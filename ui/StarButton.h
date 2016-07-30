//
//  StarButton.h
//
//  Created by Sungwoo Choi on 7/30/15.
//  Copyright (c) 2015 SungLab. All rights reserved.
//


#ifndef STARbg_H
#define STARbg_H

//#include ""

//#include "./StarUI.h"
//#include "StarView.hpp"
#include <iostream> 

#include "StarMain.h"
#include "./StarView.hpp"

//#include "../math/Matrix.h"
//#include "../renderer/StarTexture.h"

using namespace std;

//Typedef 
typedef enum 
{
	INTERFACE_CIRCLE,
	INTERFACE_RECT_VERTICAL,
	INTERFACE_RECT_HORIZONTAL
}STAR_INTERFACE;

class StarBGDelegate
{
public:
	virtual void Callback_Press(int idx)=0;
};

class StarBG:public StarView
{

public:

	/*
	* BG Properties
	*/
	StarBGDelegate* delegate;

	std::vector<Vec3> bg_position;
	std::vector<Vec3> bg_center;
	std::vector<Vec2> bg_size;
	std::vector<Vec2> bg_uv;
	std::vector<unsigned short> bg_index;
	 
	unsigned int bg_number;

//	STAR_INTERFACE Star_Interface;
	
	unsigned int vao_id;
	unsigned int vbo_id[4];


	StarBG(StarBGDelegate* _delegate=NULL)
	{
		delegate = _delegate;

		vao_id = vbo_id[0] = vbo_id[1] = vbo_id[2] = vbo_id[3] = 0;
		bg_number = 0;
        now_tick = 0.;
	
		bg_position.clear();
		bg_uv.clear();
		bg_index.clear();

		bg_center.clear();
	};

   // int texture_id;

	//StarBG* setInterface(STAR_INTERFACE interface)
	//{
	//	Star_Interface = interface;
	//	return this;
	//}

	StarBG* addBG(Vec4 rect)
	{
		bg_position.push_back(Vec3(rect.x,rect.y,-1.));
		bg_position.push_back(Vec3(rect.x+rect.z,rect.y,-1.));
		bg_position.push_back(Vec3(rect.x,rect.y+rect.w,-1.));
		bg_position.push_back(Vec3(rect.x+rect.z,rect.y+rect.w,-1.));

		bg_size.push_back(Vec2(rect.w, rect.z));

		Vec3 temp = 
		(Vec3(rect.x, rect.y, -1.)
			+ Vec3(rect.x + rect.z, rect.y, -1.)
			+ Vec3(rect.x, rect.y + rect.w, -1.)
			+ Vec3(rect.x + rect.z, rect.y + rect.w, -1.))*0.25;

		bg_center.push_back(temp);
		
		return this;
	}

	StarBG* addUV(Vec4 rect)
	{
		bg_uv.push_back(Vec2(rect.x,rect.y+rect.w));
		bg_uv.push_back(Vec2(rect.x+rect.z,rect.y+rect.w));
		bg_uv.push_back(Vec2(rect.x,rect.y));
		bg_uv.push_back(Vec2(rect.x+rect.z,rect.y));

		return this;
	}
    
    //void initialize( int _vao_id, int _vbo_id)
	void init()
	{

			 //starAnt = new StarAnt<Vec3>[5];

		/*
		 * this part is defined right before it is called
		 */
        
//        starfbo->createFBO(true,true,fbo_width,fbo_height,_fbo_id);
//        
//        int err;
//        while ((err = glGetError()) != GL_NO_ERROR) {
//            printf("\n\nOpenGL error TURNON 1: %x\n\n",err);
//        }
//        GLenum status1 = glCheckFramebufferStatus(GL_FRAMEBUFFER);
//        if (status1 != GL_FRAMEBUFFER_COMPLETE) {
//            starLOG("ERROR FBO %x\n",status1);
//        }

		// butotn number
		bg_number = bg_position.size() / 4;
		if (!bg_number)
		{
			starLOG("Error, add buttton first\n");
			return;
		}
		else
		{
			starLOG("Yes, buttton num : %d\n", bg_number);
		}

        starfbo->createVAO_INDI(&vao_id);
       
		attribute_id[0] = 0;// glGetAttribLocation(shader_program, "position");
		attribute_id[1] = 1;// glGetAttribLocation(shader_program, "inputTextureCoordinate");
        

//        starfbo->createVBO_INDI(GL_ARRAY_BUFFER, sizeof(Vec3)*bg_position.size(), (void*)&bg_position[0], GL_STATIC_DRAW, &vbo_id[0]);
//        glEnableVertexAttribArray(attribute_id[0]);
//        glVertexAttribPointer(attribute_id[0], 3, GL_FLOAT, 0, 0, 0);
        //
        //starfbo->createVBO_INDI(GL_ARRAY_BUFFER, sizeof(Vec2)*bg_uv.size(), (void*)&bg_uv[0], GL_STATIC_DRAW, &vbo_id[1]);
        //glEnableVertexAttribArray(attribute_id[1]);
        //glVertexAttribPointer(attribute_id[1], 2, GL_FLOAT, 0, 0, 0);
        //

        starLOG("test %d\n", vbo_id[0]);
		starfbo->createVBOsub_INDI(GL_ARRAY_BUFFER, 0, sizeof(Vec3)*bg_position.size(), (void*)&bg_position[0], GL_DYNAMIC_DRAW, &vbo_id[0]);
		glEnableVertexAttribArray(attribute_id[0]);
		glVertexAttribPointer(attribute_id[0], 3, GL_FLOAT, 0, 0, 0);
        
        starLOG("test %d\n", vbo_id[1]);
        int err;
        while ((err = glGetError()) != GL_NO_ERROR)
            printf("\n\nOpenGL error button: %x %d\n\n",err, vbo_id[0]);

		starfbo->createVBO_INDI(GL_ARRAY_BUFFER, sizeof(Vec2)*bg_uv.size(), (void*)&bg_uv[0], GL_STATIC_DRAW, &vbo_id[1]);
		glEnableVertexAttribArray(attribute_id[1]);
		glVertexAttribPointer(attribute_id[1], 2, GL_FLOAT, 0, 0, 0);

	/*	starfbo->createVBOsub_INDI(GL_ARRAY_BUFFER, 0, sizeof(Vec2)*bg_uv.size(), (void*)&bg_uv[0], GL_DYNAMIC_DRAW, &vbo_id[1]);
		glEnableVertexAttribArray(attribute_id[1]);
		glVertexAttribPointer(attribute_id[1], 2, GL_FLOAT, 0, 0, 0);
*/

		for (int i = 0; i < bg_number; i++)
		{
			for (int a = 0; a < 6; a++)
				bg_index.push_back(rect_Idx_Vertex[a] + 4 * i);
		}
		
        starfbo->createVBO_INDI(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short)*bg_index.size(), (void*)&bg_index[0], GL_STATIC_DRAW, &vbo_id[2]);
        Matrix_Identity(final_matrix);
		Matrix_OrthoProjection(final_matrix, width, height, 0.1,1000.);
		Matrix a;
		Matrix_Translation(a, width*-0.5, height*-0.5, 0.0);
		Matrix_MxM(final_matrix, a ,final_matrix);

		/*
		* for test
		*/
    }
    
	void update()
	{


		for (int i = 0; i < bg_number; i++)
		{
			bg_position[i * 4 + 0] = bg_center[i] - Vec3(bg_size[i] * 0.5,0.0);
			bg_position[i * 4 + 1] = bg_center[i] + Vec3(Vec2(bg_size[i].x, -bg_size[i].y)*0.5,0.0);
			bg_position[i * 4 + 2] = bg_center[i] + Vec3(Vec2(-bg_size[i].x, bg_size[i].y)*0.5,0.0);
			bg_position[i * 4 + 3] = bg_center[i] + Vec3(bg_size[i] * 0.5, 0.0);
		}
	}

    void render()
    {
        
    //    starfbo->bindFBO(fbo_id[0]);
//        glEnable(GL_DEPTH_TEST);
        
//        glClearColor(0.0, 0.0, 0.0, 1.0);
//        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

        starfbo->bindVAO_INDI(&vao_id);
        
        glViewport(0,0, width,height);
        
        glUseProgram(shader_program);
        
        startexture->bindTEXTURE(GL_TEXTURE0+texture_name[0], texture_name[0]);
        texture_id[0] = glGetUniformLocation(shader_program, "texture0");
        glUniform1i(texture_id[0],texture_name[0]);
        
//        Matrix_Identity(final_matrix);
       int a =  glGetUniformLocation(shader_program,"finalM");
//        glUniformMatrix4fv(shader_program, 1, GL_FALSE,final_matrix->s );
        glUniformMatrix4fv(a, 1, GL_FALSE, final_matrix.s);
        
        glEnable(GL_BLEND);
//        glBlendFunc(GL_ONE,GL_ZERO);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
		starfbo->bindVBO_INDI(GL_ARRAY_BUFFER, &vbo_id[0]);
        int err;
        while ((err = glGetError()) != GL_NO_ERROR)
            printf("\n\nOpenGL error button: %x %d\n\n",err, vbo_id[0]);
		glEnableVertexAttribArray(attribute_id[0]);
      
		glVertexAttribPointer(attribute_id[0], 3, GL_FLOAT, 0, 0, 0);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3)*bg_position.size(), (void*)&bg_position[0], GL_DYNAMIC_DRAW);

#ifdef ANDROID
        starfbo->bindVBO(GL_ARRAY_BUFFER,vbo_id[0]);
        glVertexAttribPointer(attribute_id[0], 3, GL_FLOAT, 0, 0, 0);
        glEnableVertexAttribArray(attribute_id[0]);
        
        starfbo->bindVBO(GL_ARRAY_BUFFER,vbo_id[1]);
        glVertexAttribPointer(attribute_id[1],2, GL_FLOAT, 0, 0, 0);
        glEnableVertexAttribArray(attribute_id[1]);
        
        starfbo->bindVBO(GL_ELEMENT_ARRAY_BUFFER, vbo_id[2]);
#endif

        glDrawElements(GL_TRIANGLES,bg_index.size(), GL_UNSIGNED_SHORT ,(void*)0);
        

        
		glDisable(GL_BLEND);
       // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
       // glEnable(GL_DEPTH_TEST);
    }

void done()
{
	bg_position.clear();
	bg_uv.clear();
	bg_index.clear();
}

/*
* Callback Functions (sending)
*/
void pressed(int idx)
{
	delegate->Callback_Press(idx);
}

/*
 *  Callback Functions  (receiving)
 */
void CallbackFPS() 
{
	
};

bool test(Vec3* center,Vec2* size, Vec2* touch)
{

	//if ((rect->x < touch->x) && (rect->x + rect->z > touch->x))
	//	if ((rect->y < touch->y) && (rect->y + rect->w > touch->y))
	//		return true;

	if ( abs(center->x-touch->x) < size->x*0.5)
		if (abs(center->y - touch->y < size->y*0.5))
			return true;
	return false;
}
void CallbackTouchBegin() 
{

	for (int i = 0; i < bg_number; i++)
	{
			//Vec4 rect = Vec4(
			//(Vec2(bg_center[i].x,bg_center[i].y) - bg_size[i] * 0.5).x
			//(Vec2(bg_center[i].x, bg_center[i].y) - bg_size[i] * 0.5).y
			//	, bg_size[i].x, bg_size[i].y);
			if (test(&bg_center[i], &bg_size[i], &(startouch->nowPos[i])))
			{
				pressed(i);
				break;
			}
	}

};

void CallbackTouchMove() 
{

};

void CallbackTouchEnd() 
{

};

void CallbackTouchCancel() 
{

};

};
#endif
