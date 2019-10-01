

#include <d3d9.h>

//オーバロードによる描画変更有

#include <d3dx9.h>
#include "Sprite.h"
#include "common.h"
#include "MyDirect3D.h"
#include "MyTex.h"
#include "debug_font.h"

static LPDIRECT3DDEVICE9 g_pDevice = NULL;
LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;
static D3DCOLOR g_color = D3DCOLOR_RGBA(255, 255, 255, 255);

static int tex;

LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer=NULL;



void Sprite_Init()
{
	g_pDevice = GetDevice();

	g_pDevice->CreateVertexBuffer(sizeof(vertex1) * 4,	//四頂点分のデータを読み込むことが可能にする
		D3DUSAGE_WRITEONLY,	//WRITEONLY:読み込み不可
		FVF_VERTEX2D,
		D3DPOOL_MANAGED,	//デバイス破壊が発生した際にダイレクトXが自動的に復旧を行う
		&g_pVertexBuffer,
		NULL);


	////////////////////////////////////////////////////////////VRAMに対してポリゴン情報を送り付ける
	//VRAMに更新をかけるため、この処理を行うときはGPUの描画処理を止める。(処理が重くなる)


	

	g_pDevice->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);

	WORD* pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);	//VRAMの０番目から借りる・VRAMのすべてを取得する・仮想アドレス(メモリとVRAMは全く違うため、VRAMのアドレスを仮想的にアドレスを作成する。)・
	pIndex[0] = 0;
	pIndex[1] = 1;
	pIndex[2] = 2;
	pIndex[3] = 1;
	pIndex[4] = 3;
	pIndex[5] = 2;

	g_pIndexBuffer->Unlock();

	///////////////////////////////////////////////////////////VRAM操作終了
}

void Sprite_SetColor(D3DCOLOR Color)
{
	g_color = Color;
}

void Sprite_Uninit()
{
	if (g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer=NULL;
		
	}
	if (g_pIndexBuffer)
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}

}




void Sprite_Draw(int Texture_id, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float zoom)
{//textureid:画像番号　dx,dy:左上　cut_x,cut_y:テクスチャ座標の左上　cut_w,cut_h：張り付けるテクスチャの部分の高さと横　angle:表示するポリゴンの傾き　cx,cy:回転軸の座標 zoom:拡大縮小

	g_pDevice = GetDevice();




	int w = Texture_GetWidth(Texture_id);	//テクスチャの高さ
	int h = Texture_GetHeight(Texture_id);	//テクスチャの幅

	float u0 = cut_x / (float)w;			//左上
	float v0 = cut_y / (float)h;			//左上
	float u1 = (cut_x + cut_w) / (float)w;	//右下
	float v1 = (cut_y + cut_h) / (float)h;	//右下




	vertex1 v[] = {
		{ D3DXVECTOR4(dx,dy,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(u0,v0) },//0左上
	{ D3DXVECTOR4(dx + w,dy,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1,v0) },//1右上
	{ D3DXVECTOR4(dx ,dy + h ,0.0f,1.0f) ,D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0,v1) },//2左下
	{ D3DXVECTOR4(dx + w  ,dy + h ,0.0f,1.0f) ,D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1,v1) }//3右下
	};







	D3DXMATRIX mtxRot;
	D3DXMatrixRotationZ(&mtxRot, angle);


	D3DXMATRIX mtxW, mtxR, mtxT, mtxIT, mtxS;	//W最終的な形　R回転　T移動　IT元の座標へ	S拡大縮小
	D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);		//移動させたオブジェクトを元の位置に戻す
	D3DXMatrixTranslation(&mtxIT, cx + dx, cy + dy, 0.0f);		//移動させたオブジェクトを元の位置に戻す
	D3DXMatrixRotationZ(&mtxR, angle);	//回転させる
	D3DXMatrixScaling(&mtxS, zoom, zoom, 1.0f);


	mtxW = mtxT * mtxS*mtxR*mtxIT;	//最終的な形を入れる

									//D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);	//0座標へ移動



	for (int i = 0; i < 4; i++)
	{
		D3DXVec4Transform(&v[i].position, &v[i].position, &mtxW);

	}
	vertex1* pv;
	g_pVertexBuffer->Lock(0, 0, (void**)&pv, D3DLOCK_DISCARD);
	memcpy(pv, v, sizeof(v));
	g_pVertexBuffer->Unlock();

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	//αブレンドを有効にする。	
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	//α値とテクスチャの値を合成させる。（この式がないとα値が無視される）

	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//ここから先に描画するRGB*今から描画するα+画面のRGB*（1-今から描画するα(0~1)）
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);



	g_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//ぼやけるが、滑らかになる。	
																		//g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//くっきり見えるが、ジャギィが目立つ

																		//g_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

																		//g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);	//カメラから水平に映るテクスチャに対して複数回計算をかけるため、きれいに映すことができる。	(Zファイトが起こらない…？)
																		//g_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 8);				//この行のコードを記述することで機能する。

																		//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//
																		//g_pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(255, 0, 0, 1));


	g_pDevice->SetFVF(FVF_VERTEX2D);




	g_pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(vertex1));	//0番めのパイプライン・

	g_pDevice->SetIndices(g_pIndexBuffer);
	g_pDevice->SetTexture(0, Texture_GetTexture(Texture_id));

	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);	//最高速描画



																		//	g_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

																		//WORD index[] = { 0,1,2,1,3,2 };	//DWORDで65536個表せるWORDよりも大きい数を扱うことができるようになる。

																		//g_pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST,0,4,2,index,D3DFMT_INDEX16,v,sizeof(vertex1));	//形式・最小頂点配列番号・

																		//頂点データを指定





}

void Sprite_Draw_Alpha(int Texture_id, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float zoom, int alpha)
{//textureid:画像番号　dx,dy:左上　cut_x,cut_y:テクスチャ座標の左上　cut_w,cut_h：張り付けるテクスチャの部分の高さと横　angle:表示するポリゴンの傾き　cx,cy:回転軸の座標 zoom:拡大縮小

	g_pDevice = GetDevice();




	int w = Texture_GetWidth(Texture_id);	//テクスチャの高さ
	int h = Texture_GetHeight(Texture_id);	//テクスチャの幅

	float u0 = cut_x / (float)w;			//左上
	float v0 = cut_y / (float)h;			//左上
	float u1 = (cut_x + cut_w) / (float)w;	//右下
	float v1 = (cut_y + cut_h) / (float)h;	//右下




	vertex1 v[] = {
		{ D3DXVECTOR4(dx,dy,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,alpha) ,D3DXVECTOR2(u0,v0) },//0左上
	{ D3DXVECTOR4(dx + w,dy,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,alpha),D3DXVECTOR2(u1,v0) },//1右上
	{ D3DXVECTOR4(dx ,dy + h ,0.0f,1.0f) ,D3DCOLOR_RGBA(255,255,255,alpha),D3DXVECTOR2(u0,v1) },//2左下
	{ D3DXVECTOR4(dx + w  ,dy + h ,0.0f,1.0f) ,D3DCOLOR_RGBA(255,255,255,alpha),D3DXVECTOR2(u1,v1) }//3右下
	};







	D3DXMATRIX mtxRot;
	D3DXMatrixRotationZ(&mtxRot, angle);


	D3DXMATRIX mtxW, mtxR, mtxT, mtxIT, mtxS;	//W最終的な形　R回転　T移動　IT元の座標へ	S拡大縮小
	D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);		//移動させたオブジェクトを元の位置に戻す
	D3DXMatrixTranslation(&mtxIT, cx + dx, cy + dy, 0.0f);		//移動させたオブジェクトを元の位置に戻す
	D3DXMatrixRotationZ(&mtxR, angle);	//回転させる
	D3DXMatrixScaling(&mtxS, zoom, zoom, 1.0f);


	mtxW = mtxT * mtxS*mtxR*mtxIT;	//最終的な形を入れる

									//D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);	//0座標へ移動



	for (int i = 0; i < 4; i++)
	{
		D3DXVec4Transform(&v[i].position, &v[i].position, &mtxW);

	}
	vertex1* pv;
	g_pVertexBuffer->Lock(0, 0, (void**)&pv, D3DLOCK_DISCARD);
	memcpy(pv, v, sizeof(v));
	g_pVertexBuffer->Unlock();

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	//αブレンドを有効にする。	
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	//α値とテクスチャの値を合成させる。（この式がないとα値が無視される）

	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//ここから先に描画するRGB*今から描画するα+画面のRGB*（1-今から描画するα(0~1)）
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);



	g_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//ぼやけるが、滑らかになる。	
																		//g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//くっきり見えるが、ジャギィが目立つ

																		//g_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

																		//g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);	//カメラから水平に映るテクスチャに対して複数回計算をかけるため、きれいに映すことができる。	(Zファイトが起こらない…？)
																		//g_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 8);				//この行のコードを記述することで機能する。

																		//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//
																		//g_pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(255, 0, 0, 1));


	g_pDevice->SetFVF(FVF_VERTEX2D);




	g_pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(vertex1));	//0番めのパイプライン・

	g_pDevice->SetIndices(g_pIndexBuffer);
	g_pDevice->SetTexture(0, Texture_GetTexture(Texture_id));

	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);	//最高速描画



																		//	g_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

																		//WORD index[] = { 0,1,2,1,3,2 };	//DWORDで65536個表せるWORDよりも大きい数を扱うことができるようになる。

																		//g_pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST,0,4,2,index,D3DFMT_INDEX16,v,sizeof(vertex1));	//形式・最小頂点配列番号・

																		//頂点データを指定





}




///////////////////////////////////////////////////試作
void Sprite_Draw_Mirror(int Texture_id, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h)
{
	//textureid:画像番号　dx,dy:左上　cut_x,cut_y:テクスチャ座標の左上　cut_w,cut_h：張り付けるテクスチャの部分の高さと横　angle:表示するポリゴンの

	g_pDevice = GetDevice();




	int w = Texture_GetWidth(Texture_id);	//テクスチャの高さ
	int h = Texture_GetHeight(Texture_id);	//テクスチャの幅

	float u0 = cut_x / (float)w;			//左上
	float v0 = cut_y / (float)h;			//左上
	float u1 = (cut_x + cut_w) / (float)w;	//右下
	float v1 = (cut_y + cut_h) / (float)h;	//右下


	vertex1 v[] = {
		{ D3DXVECTOR4(dx,dy,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255) ,D3DXVECTOR2(u0+1,v0) },//0左上
	{ D3DXVECTOR4(dx + cut_w,dy,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1+1,v0) },//1右上
	{ D3DXVECTOR4(dx ,dy + cut_h ,0.0f,1.0f) ,D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u0+1,v1) },//2左下
	{ D3DXVECTOR4(dx + cut_w  ,dy + cut_h ,0.0f,1.0f) ,D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(u1+1,v1) }//3右下
	};

	vertex1* pv;
	g_pVertexBuffer->Lock(0, 0, (void**)&pv, D3DLOCK_DISCARD);	//VRAMをロック
	memcpy(pv, v, sizeof(v));			//VRAMの仮想アドレスに対して格納
	g_pVertexBuffer->Unlock();			//書き込み終了、ロック解除

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	//αブレンドを有効にする。	
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	//α値とテクスチャの値を合成させる。（この式がないとα値が無視される）

	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//ここから先に描画するRGB*今から描画するα+画面のRGB*（1-今から描画するα(0~1)）
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);


	g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);	//1を超えた場合反転

	g_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//ぼやけるが、滑らかになる。	
																		//g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//くっきり見えるが、ジャギィが目立つ

																		//g_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

																		//g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);	//カメラから水平に映るテクスチャに対して複数回計算をかけるため、きれいに映すことができる。	(Zファイトが起こらない…？)
																		//g_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 8);				//この行のコードを記述することで機能する。

																		//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//
																		//g_pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(255, 0, 0, 1));


	g_pDevice->SetFVF(FVF_VERTEX2D);




	g_pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(vertex1));	//0番めのパイプライン・

	g_pDevice->SetIndices(g_pIndexBuffer);
	g_pDevice->SetTexture(0, Texture_GetTexture(Texture_id));

	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);	//最高速描画


}

void Sprite_Draw_Effect(int Texture_id, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float zoom)
{
	g_pDevice = GetDevice();




	int w = Texture_GetWidth(Texture_id);	//テクスチャの高さ
	int h = Texture_GetHeight(Texture_id);	//テクスチャの幅

	float u0 = cut_x / (float)w;			//左上
	float v0 = cut_y / (float)h;			//左上
	float u1 = (cut_x + cut_w) / (float)w;	//右下
	float v1 = (cut_y + cut_h) / (float)h;	//右下




	vertex1 v[] = {
		{ D3DXVECTOR4(dx,dy,0.0f,1.0f),g_color ,D3DXVECTOR2(u0,v0) },//0左上
	{ D3DXVECTOR4(dx + w,dy,0.0f,1.0f),g_color,D3DXVECTOR2(u1,v0) },//1右上
	{ D3DXVECTOR4(dx ,dy + h ,0.0f,1.0f) ,g_color,D3DXVECTOR2(u0,v1) },//2左下
	{ D3DXVECTOR4(dx + w  ,dy + h ,0.0f,1.0f) ,g_color,D3DXVECTOR2(u1,v1) }//3右下
	};







	D3DXMATRIX mtxRot;
	D3DXMatrixRotationZ(&mtxRot, angle);


	D3DXMATRIX mtxW, mtxR, mtxT, mtxIT, mtxS;	//W最終的な形　R回転　T移動　IT元の座標へ	S拡大縮小
	D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);		//移動させたオブジェクトを元の位置に戻す
	D3DXMatrixTranslation(&mtxIT, cx + dx, cy + dy, 0.0f);		//移動させたオブジェクトを元の位置に戻す
	D3DXMatrixRotationZ(&mtxR, angle);	//回転させる
	D3DXMatrixScaling(&mtxS, zoom, zoom, 1.0f);


	mtxW = mtxT * mtxS*mtxR*mtxIT;	//最終的な形を入れる

									//D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);	//0座標へ移動



	for (int i = 0; i < 4; i++)
	{
		D3DXVec4Transform(&v[i].position, &v[i].position, &mtxW);

	}
	vertex1* pv;
	g_pVertexBuffer->Lock(0, 0, (void**)&pv, D3DLOCK_DISCARD);
	memcpy(pv, v, sizeof(v));
	g_pVertexBuffer->Unlock();





	g_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//ぼやけるが、滑らかになる。	
																		//g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//くっきり見えるが、ジャギィが目立つ

																		//g_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

																		//g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);	//カメラから水平に映るテクスチャに対して複数回計算をかけるため、きれいに映すことができる。	(Zファイトが起こらない…？)
																		//g_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 8);				//この行のコードを記述することで機能する。

																		//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//
																		//g_pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(255, 0, 0, 1));



	//g_pDevice->SetTextureStageState(0, D3DTA_MODULATE, D3DTOP_MODULATE);

	g_pDevice->SetFVF(FVF_VERTEX2D);




	g_pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(vertex1));	//0番めのパイプライン・

	g_pDevice->SetIndices(g_pIndexBuffer);
	g_pDevice->SetTexture(0, Texture_GetTexture(Texture_id));

	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);	//最高速描画




}








void Sprite_Draw_HP_Bule(int Texture_id, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float zoom, float HP)
{

	g_pDevice = GetDevice();




	int w = Texture_GetWidth(Texture_id)*HP;	//テクスチャの高さ
	int h = Texture_GetHeight(Texture_id);	//テクスチャの幅

	float u0 = cut_x / (float)w;			//左上
	float v0 = cut_y / (float)h;			//左上
	float u1 = (cut_x + cut_w) / (float)w;	//右下
	float v1 = (cut_y + cut_h) / (float)h;	//右下




	vertex1 v[] = {
		{ D3DXVECTOR4(dx,dy,0.0f,1.0f),D3DCOLOR_RGBA(0,0,255,255) ,D3DXVECTOR2(u0,v0) },//0左上
	{ D3DXVECTOR4(dx + w,dy,0.0f,1.0f),D3DCOLOR_RGBA(0,0,255,255),D3DXVECTOR2(u1,v0) },//1右上
	{ D3DXVECTOR4(dx ,dy + h ,0.0f,1.0f) ,D3DCOLOR_RGBA(0,0,255,255),D3DXVECTOR2(u0,v1) },//2左下
	{ D3DXVECTOR4(dx + w  ,dy + h ,0.0f,1.0f) ,D3DCOLOR_RGBA(0,0,255,255),D3DXVECTOR2(u1,v1) }//3右下
	};


	D3DXMATRIX mtxRot;
	D3DXMatrixRotationZ(&mtxRot, angle);


	D3DXMATRIX mtxW, mtxR, mtxT, mtxIT, mtxS;	//W最終的な形　R回転　T移動　IT元の座標へ	S拡大縮小
	D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);		//移動させたオブジェクトを元の位置に戻す
	D3DXMatrixTranslation(&mtxIT, cx + dx, cy + dy, 0.0f);		//移動させたオブジェクトを元の位置に戻す
	D3DXMatrixRotationZ(&mtxR, angle);	//回転させる
	D3DXMatrixScaling(&mtxS, zoom, zoom, 1.0f);


	mtxW = mtxT * mtxS*mtxR*mtxIT;	//最終的な形を入れる

									//D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);	//0座標へ移動

	for (int i = 0; i < 4; i++)
	{
		D3DXVec4Transform(&v[i].position, &v[i].position, &mtxW);

	}
	vertex1* pv;
	g_pVertexBuffer->Lock(0, 0, (void**)&pv, D3DLOCK_DISCARD);
	memcpy(pv, v, sizeof(v));
	g_pVertexBuffer->Unlock();

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	//αブレンドを有効にする。	
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	//α値とテクスチャの値を合成させる。（この式がないとα値が無視される）

	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//ここから先に描画するRGB*今から描画するα+画面のRGB*（1-今から描画するα(0~1)）
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);



	g_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//ぼやけるが、滑らかになる。	
																		//g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//くっきり見えるが、ジャギィが目立つ

																		//g_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

																		//g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);	//カメラから水平に映るテクスチャに対して複数回計算をかけるため、きれいに映すことができる。	(Zファイトが起こらない…？)
																		//g_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 8);				//この行のコードを記述することで機能する。

																		//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//
																		//g_pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(255, 0, 0, 1));


	g_pDevice->SetFVF(FVF_VERTEX2D);




	g_pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(vertex1));	//0番めのパイプライン・

	g_pDevice->SetIndices(g_pIndexBuffer);
	g_pDevice->SetTexture(0, Texture_GetTexture(Texture_id));

	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);	//最高速描画



																		//	g_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

																		//WORD index[] = { 0,1,2,1,3,2 };	//DWORDで65536個表せるWORDよりも大きい数を扱うことができるようになる。

																		//g_pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST,0,4,2,index,D3DFMT_INDEX16,v,sizeof(vertex1));	//形式・最小頂点配列番号・

																		//頂点データを指定




}

void Sprite_Draw_HP_Green(int Texture_id, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float zoom, float HP)
{
	g_pDevice = GetDevice();




	int w = Texture_GetWidth(Texture_id)*HP;	//テクスチャの高さ
	int h = Texture_GetHeight(Texture_id);	//テクスチャの幅

	float u0 = cut_x / (float)w;			//左上
	float v0 = cut_y / (float)h;			//左上
	float u1 = (cut_x + cut_w) / (float)w;	//右下
	float v1 = (cut_y + cut_h) / (float)h;	//右下




	vertex1 v[] = {
		{ D3DXVECTOR4(dx,dy,0.0f,1.0f),D3DCOLOR_RGBA(0,255,0,255) ,D3DXVECTOR2(u0,v0) },//0左上
	{ D3DXVECTOR4(dx + w,dy,0.0f,1.0f),D3DCOLOR_RGBA(0,255,0,255),D3DXVECTOR2(u1,v0) },//1右上
	{ D3DXVECTOR4(dx ,dy + h ,0.0f,1.0f) ,D3DCOLOR_RGBA(0,255,0,255),D3DXVECTOR2(u0,v1) },//2左下
	{ D3DXVECTOR4(dx + w  ,dy + h ,0.0f,1.0f) ,D3DCOLOR_RGBA(0,255,0,255),D3DXVECTOR2(u1,v1) }//3右下
	};


	D3DXMATRIX mtxRot;
	D3DXMatrixRotationZ(&mtxRot, angle);


	D3DXMATRIX mtxW, mtxR, mtxT, mtxIT, mtxS;	//W最終的な形　R回転　T移動　IT元の座標へ	S拡大縮小
	D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);		//移動させたオブジェクトを元の位置に戻す
	D3DXMatrixTranslation(&mtxIT, cx + dx, cy + dy, 0.0f);		//移動させたオブジェクトを元の位置に戻す
	D3DXMatrixRotationZ(&mtxR, angle);	//回転させる
	D3DXMatrixScaling(&mtxS, zoom, zoom, 1.0f);


	mtxW = mtxT * mtxS*mtxR*mtxIT;	//最終的な形を入れる

									//D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);	//0座標へ移動

	for (int i = 0; i < 4; i++)
	{
		D3DXVec4Transform(&v[i].position, &v[i].position, &mtxW);

	}
	vertex1* pv;
	g_pVertexBuffer->Lock(0, 0, (void**)&pv, D3DLOCK_DISCARD);
	memcpy(pv, v, sizeof(v));
	g_pVertexBuffer->Unlock();

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	//αブレンドを有効にする。	
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	//α値とテクスチャの値を合成させる。（この式がないとα値が無視される）

	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//ここから先に描画するRGB*今から描画するα+画面のRGB*（1-今から描画するα(0~1)）
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);



	g_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//ぼやけるが、滑らかになる。	
																		//g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//くっきり見えるが、ジャギィが目立つ

																		//g_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

																		//g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);	//カメラから水平に映るテクスチャに対して複数回計算をかけるため、きれいに映すことができる。	(Zファイトが起こらない…？)
																		//g_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 8);				//この行のコードを記述することで機能する。

																		//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//
																		//g_pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(255, 0, 0, 1));


	g_pDevice->SetFVF(FVF_VERTEX2D);




	g_pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(vertex1));	//0番めのパイプライン・

	g_pDevice->SetIndices(g_pIndexBuffer);
	g_pDevice->SetTexture(0, Texture_GetTexture(Texture_id));

	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);	//最高速描画



																		//	g_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

																		//WORD index[] = { 0,1,2,1,3,2 };	//DWORDで65536個表せるWORDよりも大きい数を扱うことができるようになる。

																		//g_pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST,0,4,2,index,D3DFMT_INDEX16,v,sizeof(vertex1));	//形式・最小頂点配列番号・

																		//頂点データを指定





}

void Sprite_Draw_HP_Yellow(int Texture_id, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float zoom, float HP)
{
	g_pDevice = GetDevice();




	int w = Texture_GetWidth(Texture_id)*HP;	//テクスチャの高さ
	int h = Texture_GetHeight(Texture_id);	//テクスチャの幅

	float u0 = cut_x / (float)w;			//左上
	float v0 = cut_y / (float)h;			//左上
	float u1 = (cut_x + cut_w) / (float)w;	//右下
	float v1 = (cut_y + cut_h) / (float)h;	//右下




	vertex1 v[] = {
		{ D3DXVECTOR4(dx,dy,0.0f,1.0f),D3DCOLOR_RGBA(255,255,0,255),D3DXVECTOR2(u0,v0) },//0左上
	{ D3DXVECTOR4(dx + w,dy,0.0f,1.0f),D3DCOLOR_RGBA(255,255,0,255),D3DXVECTOR2(u1,v0) },//1右上
	{ D3DXVECTOR4(dx ,dy + h ,0.0f,1.0f) ,D3DCOLOR_RGBA(255,255,0,255),D3DXVECTOR2(u0,v1) },//2左下
	{ D3DXVECTOR4(dx + w  ,dy + h ,0.0f,1.0f) ,D3DCOLOR_RGBA(255,255,0,255),D3DXVECTOR2(u1,v1) }//3右下
	};


	D3DXMATRIX mtxRot;
	D3DXMatrixRotationZ(&mtxRot, angle);


	D3DXMATRIX mtxW, mtxR, mtxT, mtxIT, mtxS;	//W最終的な形　R回転　T移動　IT元の座標へ	S拡大縮小
	D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);		//移動させたオブジェクトを元の位置に戻す
	D3DXMatrixTranslation(&mtxIT, cx + dx, cy + dy, 0.0f);		//移動させたオブジェクトを元の位置に戻す
	D3DXMatrixRotationZ(&mtxR, angle);	//回転させる
	D3DXMatrixScaling(&mtxS, zoom, zoom, 1.0f);


	mtxW = mtxT * mtxS*mtxR*mtxIT;	//最終的な形を入れる

									//D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);	//0座標へ移動

	for (int i = 0; i < 4; i++)
	{
		D3DXVec4Transform(&v[i].position, &v[i].position, &mtxW);

	}
	vertex1* pv;
	g_pVertexBuffer->Lock(0, 0, (void**)&pv, D3DLOCK_DISCARD);
	memcpy(pv, v, sizeof(v));
	g_pVertexBuffer->Unlock();

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	//αブレンドを有効にする。	
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	//α値とテクスチャの値を合成させる。（この式がないとα値が無視される）

	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//ここから先に描画するRGB*今から描画するα+画面のRGB*（1-今から描画するα(0~1)）
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);



	g_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//ぼやけるが、滑らかになる。	
																		//g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//くっきり見えるが、ジャギィが目立つ

																		//g_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

																		//g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);	//カメラから水平に映るテクスチャに対して複数回計算をかけるため、きれいに映すことができる。	(Zファイトが起こらない…？)
																		//g_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 8);				//この行のコードを記述することで機能する。

																		//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//
																		//g_pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(255, 0, 0, 1));


	g_pDevice->SetFVF(FVF_VERTEX2D);




	g_pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(vertex1));	//0番めのパイプライン・

	g_pDevice->SetIndices(g_pIndexBuffer);
	g_pDevice->SetTexture(0, Texture_GetTexture(Texture_id));

	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);	//最高速描画



																		//	g_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

																		//WORD index[] = { 0,1,2,1,3,2 };	//DWORDで65536個表せるWORDよりも大きい数を扱うことができるようになる。

																		//g_pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST,0,4,2,index,D3DFMT_INDEX16,v,sizeof(vertex1));	//形式・最小頂点配列番号・

																		//頂点データを指定




}

void Sprite_Draw_HP_Red(int Texture_id, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float zoom, float HP)
{
	g_pDevice = GetDevice();




	int w = Texture_GetWidth(Texture_id)*HP;	//テクスチャの高さ
	int h = Texture_GetHeight(Texture_id);	//テクスチャの幅

	float u0 = cut_x / (float)w;			//左上
	float v0 = cut_y / (float)h;			//左上
	float u1 = (cut_x + cut_w) / (float)w;	//右下
	float v1 = (cut_y + cut_h) / (float)h;	//右下




	vertex1 v[] = {
		{ D3DXVECTOR4(dx,dy,0.0f,1.0f),D3DCOLOR_RGBA(255,0,0,255),D3DXVECTOR2(u0,v0) },//0左上
	{ D3DXVECTOR4(dx + w,dy,0.0f,1.0f),D3DCOLOR_RGBA(255,0,0,255),D3DXVECTOR2(u1,v0) },//1右上
	{ D3DXVECTOR4(dx ,dy + h ,0.0f,1.0f) ,D3DCOLOR_RGBA(255,0,0,255),D3DXVECTOR2(u0,v1) },//2左下
	{ D3DXVECTOR4(dx + w  ,dy + h ,0.0f,1.0f) ,D3DCOLOR_RGBA(255,0,0,255),D3DXVECTOR2(u1,v1) }//3右下
	};


	D3DXMATRIX mtxRot;
	D3DXMatrixRotationZ(&mtxRot, angle);


	D3DXMATRIX mtxW, mtxR, mtxT, mtxIT, mtxS;	//W最終的な形　R回転　T移動　IT元の座標へ	S拡大縮小
	D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);		//移動させたオブジェクトを元の位置に戻す
	D3DXMatrixTranslation(&mtxIT, cx + dx, cy + dy, 0.0f);		//移動させたオブジェクトを元の位置に戻す
	D3DXMatrixRotationZ(&mtxR, angle);	//回転させる
	D3DXMatrixScaling(&mtxS, zoom, zoom, 1.0f);


	mtxW = mtxT * mtxS*mtxR*mtxIT;	//最終的な形を入れる

									//D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);	//0座標へ移動

	for (int i = 0; i < 4; i++)
	{
		D3DXVec4Transform(&v[i].position, &v[i].position, &mtxW);

	}
	vertex1* pv;
	g_pVertexBuffer->Lock(0, 0, (void**)&pv, D3DLOCK_DISCARD);
	memcpy(pv, v, sizeof(v));
	g_pVertexBuffer->Unlock();

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);	//αブレンドを有効にする。	
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	//α値とテクスチャの値を合成させる。（この式がないとα値が無視される）

	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		//ここから先に描画するRGB*今から描画するα+画面のRGB*（1-今から描画するα(0~1)）
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);



	g_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	//ぼやけるが、滑らかになる。	
																		//g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	//くっきり見えるが、ジャギィが目立つ

																		//g_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

																		//g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);	//カメラから水平に映るテクスチャに対して複数回計算をかけるため、きれいに映すことができる。	(Zファイトが起こらない…？)
																		//g_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, 8);				//この行のコードを記述することで機能する。

																		//g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	//
																		//g_pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(255, 0, 0, 1));


	g_pDevice->SetFVF(FVF_VERTEX2D);




	g_pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(vertex1));	//0番めのパイプライン・

	g_pDevice->SetIndices(g_pIndexBuffer);
	g_pDevice->SetTexture(0, Texture_GetTexture(Texture_id));

	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);	//最高速描画



																		//	g_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

																		//WORD index[] = { 0,1,2,1,3,2 };	//DWORDで65536個表せるWORDよりも大きい数を扱うことができるようになる。

																		//g_pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST,0,4,2,index,D3DFMT_INDEX16,v,sizeof(vertex1));	//形式・最小頂点配列番号・

																		//頂点データを指定






}






