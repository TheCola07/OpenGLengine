#include "TGATexture.h"

//����TGAͼ����ѹ����ʽ������������
bool LoadTGA(TextureImage* texture, char* filename)			//����.TGA�ļ�������
{
	GLubyte		TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };	//û��ѹ����TGA Header
	GLubyte		TGAcompare[12];								//�����Ƚ�TGA Header
	GLubyte		header[6];									//Header�ͷ���������ֽ�
	GLuint		bytesPerPixel;								//����TGA�ļ���ÿ�������õ����ֽ���
	GLuint		imageSize;									//�����������������ͼ��Ĵ�С
	GLuint		temp;										//��ʱ����
	GLuint		type = GL_RGBA;								//��Ĭ�ϵ�GLģʽ����ΪRBGA��32 BPP��

	FILE* file = fopen(filename, "rb");						// ���ļ�

	if (file == NULL ||										// �ļ��Ƿ����
		fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare) ||	// �Ƿ���24���ض�ȡ
		memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0 ||	// ���ͷ�ļ��Ƿ���������Ҫ��
		fread(header, 1, sizeof(header), file) != sizeof(header))				// ��ȡ��������ͷ�ֽ�
	{
		if (file == NULL)									// �ļ��Ƿ����
			return false;									
		else
		{
			fclose(file);									// �ر��ļ�
			return false;									
		}
	}

	texture->width = header[1] * 256 + header[0];			// ȷ��TGA�ļ��Ŀ��(highbyte*256+lowbyte)
	texture->height = header[3] * 256 + header[2];			// ȷ��TGA�ļ��ĳ���(highbyte*256+lowbyte)

	//OpenGL������ֻ��ʹ��24λ����32λ��TGAͼ��
	if (texture->width <= 0 ||								
		texture->height <= 0 ||								
		(header[4] != 24 && header[4] != 32))					// TGA�Ƿ�Ϊ24λ����32λ
	{
		fclose(file);										//�ر��ļ�
		return false;										
	}

	texture->bpp = header[4];							// ��ȡTGAÿ���ض�Ӧ�ı�����(24 or 32)
	bytesPerPixel = texture->bpp / 8;						
	imageSize = texture->width * texture->height * bytesPerPixel;	// ����TGA�ļ�����Ҫ�Ŀռ��С

	texture->imageData = (GLubyte*)malloc(imageSize);		// ����ռ�

	if (texture->imageData == NULL ||							// ͼ�������Ƿ����
		fread(texture->imageData, 1, imageSize, file) != imageSize)	// ӳ���С��Ԥ�����ڴ�ƥ����?
	{
		if (texture->imageData != NULL)						// ͼ���ַ񱻶�ȡ
			free(texture->imageData);						

		fclose(file);										
		return false;										
	}

	//RGB���ݸ�ʽת����������OpenGL��ʹ��
	for (GLuint i = 0; i<int(imageSize); i += bytesPerPixel)		// ѭ����ȡͼ������
	{														// ������1�͵�3���ֽ�(Red��Blue)
		temp = texture->imageData[i];							
		texture->imageData[i] = texture->imageData[i + 2];	
		texture->imageData[i + 2] = temp;					
	}

	fclose(file);											// �ر��ļ�

	// ��������
	glGenTextures(1, &texture[0].texID);					// ��������

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);			// ������������
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// �����˲�
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// �����˲�

	if (texture[0].bpp == 24)									// TGA�ļ��Ƿ�Ϊ24λ
	{
		type = GL_RGB;										// ����ΪRGBģʽ
	}

	glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);

	return true;											
}