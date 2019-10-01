
#define CONIOEX

#include "conioex.h"

typedef struct	//status�^�̍쐬
{
	char name[35];
	float hp;
	int mp;
	int def;
	int speed;
	char element[6];
	char skill[35];
	int existance;
}status;

extern status character[4];

int create(int notsaved)	//�L�����N�^�쐬
{
	system("cls");	//��ʃ��Z�b�g

	int select;

	printf("\n1:%s\n\n2:%s\n\n3:%s\n\n4:%s\n\n\n���Ԗڂ̃L�����N�^��ݒ肵�܂����H  (0�Ŗ߂�)", character[0].name, character[1].name, character[2].name, character[3].name);	//�L�����N�^�[���Ɣԍ���\��

	select = _getch();	//�ԍ���I��

	for (select; select != '0'&&select != '1'&&select != '2'&&select != '3'&&select != '4';)	//��O�����i������x���́j
	{
		system("cls");
		printf("������x���͂��Ă��������B\n\n");
		printf("\n1:%s\n\n2:%s\n\n3:%s\n\n4:%s\n\n\n���Ԗڂ̃L�����N�^��ݒ肵�܂����H  (0�Ŗ߂�)", character[0].name, character[1].name, character[2].name, character[3].name);

		select = _getch();
	}


	if (select == '0')
	{
		return notsaved;	//0����͂����ꍇ�A���j���[�֖߂�(main��)
	}



	system("cls");
	printf("�Ȃ܂����ɂイ��傭���Ă��������B\n\n�@���O:");

	setcursortype(SOLIDCURSOR);	//�J�[�\����\��

	scanf("%s", character[select - '1'].name);	//���O�̓���
	rewind(stdin);

	for (select; _mbstrlen(character[select - '1'].name) <= 1 || _mbstrlen(character[select - '1'].name) > 20;)	//���O���Z���ꍇ�ƒ����ꍇ�̍ē��͊J�n
	{
		system("cls");
		if (strlen(character[select - '1'].name) <= 1)
		{
			printf("\n���O���Z�����܂��I\n\n������x���͂��Ă�������\n");
			printf("\n���O�F");
		}
		else if (strlen(character[select - '1'].name) > 20)
		{
			printf("\n���O���������܂��I\n\n������x���͂��Ă�������\n");
			printf("\n���O�F");
		}

		scanf("\n%s", character[select - '1'].name);
		rewind(stdin);

	}

	setcursortype(NOCURSOR);	//�J�[�\���\��������

	int count = strlen(character[select - '1'].name);	//�����R�[�h����肷��񐔂̏����l

	int total = 0;		//�����R�[�h�̍��v�l
	int ep = 0;			//element point �����l
	int max;	//�e�X�e�[�^�X�̍ő�l




				////////////////////////////////////////////////////////�p�����[�^�ݒ�J�n

	for (int i = 0; i < count; i++)
	{

		total += abs(character[select - '1'].name[i]);	//���ׂĂ̕����R�[�h�̍��v�l���v��

	}

	ep = total % 10;		//�R�[�h���v�l�̈ꌅ�ڂ��v���@(��ɂ�������Ƃɑ��������߂�)


	total = total / count;	//���v�l����A�S�̂̕��ς����


	printf("\n\n\n\n\n");

	character[select - '1'].hp = abs(character[select - '1'].name[1]) + total;	//��ڂ̕����R�[�h�ɕ��ϒl�𑫂����l��̗͂ɂ���
	int HP = character[select - '1'].hp;	//�X�s�[�h�̌v�Z�̂��߂�int�^�̕ϐ��֊i�[����B
	character[select - '1'].mp = abs(character[select - '1'].name[3]) + total;	//�l�ڂ̕����R�[�h�ɕ��ϒl�𑫂����l���U���ɂ���
	character[select - '1'].def = total * 2;	//���ϒl��2�{�ɂ����l��h��͂ɂ���B
	character[select - '1'].speed = (HP + character[select - '1'].mp + character[select - '1'].def) % 100;	//���ׂẴX�e�[�^�X�����v���A����̏\���ڂ܂ł��X�s�[�h�Ƃ���B


	max = character[select - '1'].hp;	//max�ɑ̗͒l���i�[
	int sp = 1;	//�X�L���̏����l���P�ɂ��Ă����B

	if (max < character[select - '1'].mp)
	{
		max = character[select - '1'].mp;	//max�ɍU���l���i�[
		sp = 2;	//�̗͂����U�����傫����΃X�L���̐��l���Q�ɂ���
	}
	if (max < character[select - '1'].def)
	{
		max = character[select - '1'].def;
		sp = 3;	//�̗͂܂��͍U���͂����h�䂪�傫����΃X�L���̐��l���R�ɂ���B
	}


	if (ep == 0)	//�R�[�h���v�l��0�̏ꍇ
	{
		strcpy(character[select - '1'].element, "��");

		if (sp == 1)	//�e�X�e�[�^�X���̗͂��ō��̏ꍇ
		{
			strcpy(character[select - '1'].skill, "�o��");
		}
		else if (sp == 2)	//�e�X�e�[�^�X���U�����ō��̏ꍇ
		{
			strcpy(character[select - '1'].skill, "�I�[�o�[�N���b�N");
		}
		else if (sp == 3)	//�e�X�e�[�^�X���h�䂪�ō��̏ꍇ
		{
			strcpy(character[select - '1'].skill, "�G�������g�u���C�N");
		}
	}

	if (ep == 1 || ep == 2)	//�R�[�h���v�l��1��2�̏ꍇ
	{
		strcpy(character[select - '1'].element, "��");

		if (sp == 1)	//�e�X�e�[�^�X���̗͂��ō��̏ꍇ
		{
			strcpy(character[select - '1'].skill, "��e�͂Ȃ��̑唚��");
		}
		else if (sp == 2)	//�e�X�e�[�^�X���U�����ō��̏ꍇ
		{
			strcpy(character[select - '1'].skill, "�A�g�~�b�N�C���p�N�g");
		}
		else if (sp == 3)		//�e�X�e�[�^�X���h�䂪�ō��̏ꍇ
		{
			strcpy(character[select - '1'].skill, "���e�I���C�g");
		}
	}
	if (ep == 3 || ep == 4)	//�R�[�h���v�l��3��4�̏ꍇ
	{
		strcpy(character[select - '1'].element, "��");

		if (sp == 1)	//�e�X�e�[�^�X���̗͂��ō��̏ꍇ
		{
			strcpy(character[select - '1'].skill, "�I�[�V�����Y�A�M�g");
		}
		else if (sp == 2)	//�e�X�e�[�^�X���U�����ō��̏ꍇ
		{
			strcpy(character[select - '1'].skill, "�C�n�I�P�A�m�X");
		}
		else if (sp == 3)	//�e�X�e�[�^�X���h�䂪�ō��̏ꍇ
		{
			strcpy(character[select - '1'].skill, "���Ԑ���");
		}

	}
	if (ep == 5 || ep == 6)	//�R�[�h���v�l��5��6�̏ꍇ
	{
		strcpy(character[select - '1'].element, "��");

		if (sp == 1)	//�e�X�e�[�^�X���̗͂��ō��̏ꍇ
		{
			strcpy(character[select - '1'].skill, "���C�W���O�X�g�[��");
		}
		else if (sp == 2)	//�e�X�e�[�^�X���U�����ō��̏ꍇ
		{
			strcpy(character[select - '1'].skill, "�����{��");
		}
		else if (sp == 3)	//�e�X�e�[�^�X���h�䂪�ō��̏ꍇ
		{
			strcpy(character[select - '1'].skill, "�T�C�N�����G�b�W");
		}

	}
	if (ep == 7)	//�R�[�h���v�l��7�̏ꍇ
	{
		strcpy(character[select - '1'].element, "��");

		if (sp == 1)	//�e�X�e�[�^�X���̗͂��ō��̏ꍇ
		{
			strcpy(character[select - '1'].skill, "���C�g�j���O�X���b�V��");
		}
		else if (sp == 2)	//�e�X�e�[�^�X���U�����ō��̏ꍇ
		{
			strcpy(character[select - '1'].skill, "�A�[�N�u���X�g");
		}
		else if (sp == 3)	//�e�X�e�[�^�X���h�䂪�ō��̏ꍇ
		{
			strcpy(character[select - '1'].skill, "�}�}���K��");
		}

	}
	if (ep == 8)	//�R�[�h���v�l��8�̏ꍇ
	{
		strcpy(character[select - '1'].element, "��");

		if (sp == 1)	//�e�X�e�[�^�X���̗͂��ō��̏ꍇ
		{
			strcpy(character[select - '1'].skill, "�����̖���");
		}
		else if (sp == 2)	//�e�X�e�[�^�X���U�����ō��̏ꍇ
		{
			strcpy(character[select - '1'].skill, "�V���C�j���O�X�s�A");
		}
		else if (sp == 3)	//�e�X�e�[�^�X���h�䂪�ō��̏ꍇ
		{
			strcpy(character[select - '1'].skill, "�����̌�");
		}

	}
	if (ep == 9)	//�R�[�h���v�l��9�̏ꍇ
	{
		strcpy(character[select - '1'].element, "��");

		if (sp == 1)	//�e�X�e�[�^�X���̗͂��ō��̏ꍇ
		{
			strcpy(character[select - '1'].skill, "���̖���");
		}
		else if (sp == 2)	//�e�X�e�[�^�X���U�����ō��̏ꍇ
		{
			strcpy(character[select - '1'].skill, "�u���b�f�B�M�A");
		}
		else if (sp == 3)	//�e�X�e�[�^�X���h�䂪�ō��̏ꍇ
		{
			strcpy(character[select - '1'].skill, "�u���b�N�A�|�J���v�X");
		}

	}


	character[select - '1'].hp *= 4.3;	//�̗͂𑝂₵�A�퓬���Ԃ�L�΂�

	character[select - '1'].existance = 1;		//�ϐ��ɂP�����B���̃L�����N�^�[�����݂��邱�Ƃ�����




												//�X�e�[�^�X�ݒ茋��
	printf("\n\n�̗�:%.0f", character[select - '1'].hp);	//�̗͂̕\���ƕ]��
	if (character[select - '1'].hp >= 900)
	{
		textcolor(LIGHTRED);
		printf("\n�����I�I\n");
		textcolor(WHITE);
	}
	else if (character[select - '1'].hp >= 700 && character[select - '1'].hp < 900)
	{
		textcolor(LIGHTCYAN);
		printf("\n�܂��܂�\n");
		textcolor(WHITE);
	}
	else
	{
		textcolor(LIGHTGRAY);
		printf("\n�ア�c\n");
		textcolor(WHITE);
	}


	printf("\n����:%d", character[select - '1'].mp);	//�U���͂̕\���ƕ]��
	if (character[select - '1'].mp >= 200)
	{
		textcolor(LIGHTRED);
		printf("\n�����I�I\n");
		textcolor(WHITE);
	}
	else if (character[select - '1'].mp >= 167 && character[select - '1'].mp <= 199)
	{
		textcolor(LIGHTCYAN);
		printf("\n�܂��܂�\n");
		textcolor(WHITE);
	}
	else
	{
		textcolor(LIGHTGRAY);
		printf("\n�ア�c\n");
		textcolor(WHITE);
	}



	printf("\n�h��:%d", character[select - '1'].def);		//�h��͂̕\���ƕ]��
	if (character[select - '1'].def >= 200)
	{
		textcolor(LIGHTRED);
		printf("\n�����I\n");
		textcolor(WHITE);
	}
	else if (character[select - '1'].def >= 167 && character[select - '1'].def <= 199)
	{
		textcolor(LIGHTCYAN);
		printf("\n�܂��܂�\n");
		textcolor(WHITE);
	}
	else
	{
		textcolor(LIGHTGRAY);
		printf("\n�ア�c\n");
		textcolor(WHITE);
	}

	printf("\n���x:%d", character[select - '1'].speed);	//�X�s�[�h�̕\���ƕ]��
	if (character[select - '1'].speed >= 75)
	{
		textcolor(LIGHTRED);
		printf("\n�����I�I\n");
		textcolor(WHITE);
	}
	else if (character[select - '1'].speed >= 40 && character[select - '1'].speed <= 74)
	{
		textcolor(LIGHTCYAN);
		printf("\n�܂��܂�\n");
		textcolor(WHITE);
	}
	else
	{
		textcolor(LIGHTGRAY);
		printf("\n�x���c\n");
		textcolor(WHITE);
	}

	printf("\n����:");

	//�������ƂɃe�L�X�g�J���\��ύX����
	if (ep == 0)	//������
	{
		textcolor(LIGHTGRAY);
	}
	if (ep == 1 || ep == 2)	//������
	{
		textcolor(LIGHTRED);
	}
	if (ep == 3 || ep == 4)	//������
	{
		textcolor(LIGHTCYAN);
	}
	if (ep == 5 || ep == 6)	//������
	{
		textcolor(LIGHTGREEN);
	}
	if (ep == 7 || ep == 8)	//�������E������
	{
		textcolor(YELLOW);
	}
	if (ep == 9)	//�ő���
	{
		textcolor(LIGHTMAGENTA);
	}
	printf("%s\n", character[select - '1'].element);
	textcolor(WHITE);
	printf("\n�X�L��:");
	if (ep == 0)	//������
	{
		textcolor(LIGHTGRAY);
	}
	if (ep == 1 || ep == 2)	//������
	{
		textcolor(LIGHTRED);
	}
	if (ep == 3 || ep == 4)	//������
	{
		textcolor(LIGHTCYAN);
	}
	if (ep == 5 || ep == 6)	//������
	{
		textcolor(LIGHTGREEN);
	}
	if (ep == 7 || ep == 8)	//�������E������
	{
		textcolor(YELLOW);
	}
	if (ep == 9)	//�ő���
	{
		textcolor(LIGHTMAGENTA);
	}

	printf("<< %s >>", character[select - '1'].skill);

	////�X�L���̐���
	if (ep == 0)	//������
	{
		textcolor(LIGHTGRAY);
		switch (sp)
		{
		case 1:printf("\n   �����͂Ȃ��Ƃ��A���̋����M�O�����ɂ̗͂��Ăъo�܂��Q�Q�I�I"); break;
		case 2:printf("\n   �������������āA���ׂĂ𒴉z�����͂��Q�Q�I�I"); break;
		case 3:printf("\n   �l�Ԃ��_�̎��s��ɉ߂��Ȃ��̂��A\n   �_���l�Ԃ̎��s��ɉ߂��Ȃ��̂��B\n\n      �Q�Q�t���[�h���q�E���B���w�����E�j�[�`�F");
		}
	}
	if (ep == 1 || ep == 2)	//������
	{
		textcolor(LIGHTRED);
		switch (sp)
		{
		case 1:printf("\n   �����̔@�����̎E�ӂ́A�n���Ă��V�����ł����B\n   ���ׂĂ�R�₷�o��͂��邩�Q�Q�H"); break;
		case 2:printf("\n   �R����ӎu�̑O�ɁA�h��Ȃǖ��͂ł����Ȃ��B\n   ����̖h������󂹁I"); break;
		case 3:printf("\n   �V���U��~�낳�ꂵ�S�Ƃ́A���ʂ��邱�ƂȂ��A�S�ē������@���ׂ��B");
		}
	}
	if (ep == 3 || ep == 4)	//������
	{
		textcolor(LIGHTCYAN);
		switch (sp)
		{
		case 1:printf("\n   �t�炤���̑S�Ă����ݍ��ފC�B\n   ���̃A�M�g�ő���̍U������炦�I"); break;
		case 2:printf("\n   ��C���������􂭐n�A���̖��̓I�P�A�m�X�B\n   ����̖h��𖳎������U���I"); break;
		case 3:printf("\n   �Ɍ��𒴂����e�C�́A�S�Ă����Ȃ��A�S�Ă𖳂ɋA���B\n   �V���ɁA���Ԑ����̔@���B"); break;
		}
	}
	if (ep == 5 || ep == 6)	//������
	{
		textcolor(LIGHTGREEN);
		switch (sp)
		{
		case 1:printf("\n   �삯�オ��A���̕��Ƌ��ɁI\n   ���g�̍U���Ɩh�䂪�㏸�I"); break;
		case 2:printf("\n   �₦�ԂȂ��{���̘A���I\n   �r�Ԃ镗�̗͂�@�����߁I"); break;
		case 3:printf("\n   �G��؂肳���͎����̐n�I\n   ���g�̑��x�������قǈЗ͂��㏸�I"); break;
		}
	}
	if (ep == 7)//������
	{
		textcolor(YELLOW);
		switch (sp)
		{
		case 1:printf("\n   ��������􂭎��d�̈�M�B\n   ����̖h�䂪����������Ԃŋ��͂Ȉꌂ�I"); break;
		case 2:printf("\n   ���̓{��́A�����Ƌ��ɖ苿���Q�Q\n   �̗͂��]���ɁA���͂Ȉꌂ�I"); break;
		case 3:printf("\n   ���ׁI�����I���̙��K�͑�n�����h�邪���I�I\n   �U���Ɩh������킹�����͂Ȉꌂ�I"); break;
		}
	}
	if (ep == 8)	//������
	{
		textcolor(YELLOW);
		switch (sp)
		{
		case 1:printf("\n   �n�܂���������A���̖������V�t�F���B\n   �U���Ɩh���㏞�ɋ��͂Ȉꌂ"); break;
		case 2:printf("\n   �C���������Ɋт�����̂͂Ȃ��B\n   ����̖h��𖳎������U���I"); break;
		case 3:printf("\n   �S�Ă��~�����A�l�͂������ՂƌĂԁB\n   �h�䂪�㏸���A���^�[�������񕜌��ʕt�^�I"); break;
		}
	}
	if (ep == 9)	//�ő���
	{
		textcolor(LIGHTMAGENTA);
		switch (sp)
		{
		case 1:printf("\n   �I���ɂ��߂������A���̖����V�������B\n   �U���Ɩh���㏞�ɋ��͂Ȉꌂ"); break;
		case 2:printf("\n   �K�����Ԃ͐�������ۂݍ��݉�������Q�Q�B\n   �̗͂��]���ɂ��A�U���Ɩh���傫���㏸"); break;
		case 3:printf("\n   �u�D���v�A���ꂪ�ł̐_���Ȃ�B\n   ����̖h���D�����A�����̍U���͂��㏸�I"); break;
		}
	}

	textcolor(WHITE);




	getch();

	system("cls");

	notsaved = 1;	//�Z�[�u�����{������

	return notsaved;	//���j���[(main)�֖߂�
}