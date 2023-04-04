#include "TGATexture.h"

//加载TGA图像（无压缩格式），生成纹理
bool LoadTGA(TextureImage* texture, char* filename)			//载入.TGA文件的内容
{
	GLubyte		TGAheader[12] = { 0,0,2,0,0,0,0,0,0,0,0,0 };	//没有压缩的TGA Header
	GLubyte		TGAcompare[12];								//用来比较TGA Header
	GLubyte		header[6];									//Header里，头六个有用字节
	GLuint		bytesPerPixel;								//保存TGA文件里每个像素用到的字节数
	GLuint		imageSize;									//用来保存随机产生的图像的大小
	GLuint		temp;										//临时变量
	GLuint		type = GL_RGBA;								//将默认的GL模式设置为RBGA（32 BPP）

	FILE* file = fopen(filename, "rb");						// 打开文件

	if (file == NULL ||										// 文件是否存在
		fread(TGAcompare, 1, sizeof(TGAcompare), file) != sizeof(TGAcompare) ||	// 是否以24比特读取
		memcmp(TGAheader, TGAcompare, sizeof(TGAheader)) != 0 ||	// 这个头文件是否是我们需要的
		fread(header, 1, sizeof(header), file) != sizeof(header))				// 读取下面六个头字节
	{
		if (file == NULL)									// 文件是否存在
			return false;									
		else
		{
			fclose(file);									// 关闭文件
			return false;									
		}
	}

	texture->width = header[1] * 256 + header[0];			// 确定TGA文件的宽度(highbyte*256+lowbyte)
	texture->height = header[3] * 256 + header[2];			// 确定TGA文件的长度(highbyte*256+lowbyte)

	//OpenGL中纹理只能使用24位或者32位的TGA图像
	if (texture->width <= 0 ||								
		texture->height <= 0 ||								
		(header[4] != 24 && header[4] != 32))					// TGA是否为24位或者32位
	{
		fclose(file);										//关闭文件
		return false;										
	}

	texture->bpp = header[4];							// 获取TGA每像素对应的比特数(24 or 32)
	bytesPerPixel = texture->bpp / 8;						
	imageSize = texture->width * texture->height * bytesPerPixel;	// 计算TGA文件所需要的空间大小

	texture->imageData = (GLubyte*)malloc(imageSize);		// 分配空间

	if (texture->imageData == NULL ||							// 图像内容是否存在
		fread(texture->imageData, 1, imageSize, file) != imageSize)	// 映像大小与预留的内存匹配吗?
	{
		if (texture->imageData != NULL)						// 图像手否被读取
			free(texture->imageData);						

		fclose(file);										
		return false;										
	}

	//RGB数据格式转换，便于在OpenGL中使用
	for (GLuint i = 0; i<int(imageSize); i += bytesPerPixel)		// 循环读取图像数据
	{														// 交换第1和第3个字节(Red和Blue)
		temp = texture->imageData[i];							
		texture->imageData[i] = texture->imageData[i + 2];	
		texture->imageData[i + 2] = temp;					
	}

	fclose(file);											// 关闭文件

	// 创建纹理
	glGenTextures(1, &texture[0].texID);					// 生成纹理

	glBindTexture(GL_TEXTURE_2D, texture[0].texID);			// 加载纹理数据
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// 线性滤波
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// 线性滤波

	if (texture[0].bpp == 24)									// TGA文件是否为24位
	{
		type = GL_RGB;										// 设置为RGB模式
	}

	glTexImage2D(GL_TEXTURE_2D, 0, type, texture[0].width, texture[0].height, 0, type, GL_UNSIGNED_BYTE, texture[0].imageData);

	return true;											
}