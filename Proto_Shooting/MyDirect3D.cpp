
#include <d3d9.h>
#include <d3dx9.h>
#include "MyDirect3D.h"
#include "common.h"
#include "MyTex.h"
#include "Sprite.h"
#include "system_timer.h"
#include "debug_font.h"

#define CP (100*2*D3DX_PI)	//背景*2*π
#define RADIAN (D3DX_PI*2/CP)


static LPDIRECT3D9 g_pD3D = NULL;
static LPDIRECT3DDEVICE9 g_pDevice = NULL;

D3DPRESENT_PARAMETERS d3dpp = {};


bool MyDirect3D_Init(HWND hWnd)
{

	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		MessageBox(NULL, "デバイスの取得に失敗しました。", "警告", MB_OK);
		return false;
	}

	d3dpp.BackBufferWidth = SCREEN_WIDTH;			//画面サイズ
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;		//画面サイズ
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	//ウィンドウサイズを指定(未知数)
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = true;	//ウィンドウならtrue　フルスクリーンならfalse
	d3dpp.EnableAutoDepthStencil = TRUE;	//深度バッファ・ステンシルバッファを有効にする。(Zバッファ：ポリゴンの前後を判断する。)
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	//IMMEDIATE:後に使うかも…？(垂直同期を待機せずに画面を更新する。コンピュータの処理に合わせて更新するため60ｆ以上になる。)


	HRESULT hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice);
																																		  //HRESULT hr3 = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice);//どのモニターを使うか、どのアダプタを使うか。	//HAL:HardwareAcceLeration
																													  //FAILEDマクロ内にHRESULT型の変数を入れることで、ウィンドウ更新に失敗していた場合の処理ができるようになる。
	if (FAILED(hr))
	{
		MessageBox(NULL,"デバイスエラーが発生しました。", "エラー", MB_OK);
		return false;
	}

	return true;	//最後に書く
}


void MyDirect3D_Uninit(void)
{
	if (g_pDevice != NULL)	//デバイスの返却
	{
		g_pDevice->Release();	//g_pD3Dのアドレスをすべて解放
		g_pDevice = NULL;	//g_pD3Dアドレスを解放。
	}

	if (g_pD3D != NULL)	//インターフェースの返却
	{
		g_pD3D->Release();	//g_pD3Dのアドレスをすべて解放
		g_pD3D = NULL;	//g_pD3Dアドレスを解放
	}
}




	



LPDIRECT3DDEVICE9 GetDevice()
{

	return g_pDevice;

}
