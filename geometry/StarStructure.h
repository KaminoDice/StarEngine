//
//  StarStructure.h
//  GeoArt
//
//  Created by Sungwoo Choi on 7/31/15.
//  Copyright (c) 2015 SungLab. All rights reserved.
//

#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdio.h>
#include "../starMain.h"

typedef struct Vertex_OBJ_
{
    Vec3 position;
    Vec2 texture_coord;
    Vec3 normal;
}Vertex_OBJ;

typedef struct Vertex_RGB_
{
    Vec3 position;
    Color3 color;
    Vec3 normal;
}Vertex_RGB;

typedef struct Vertex_TEX_
{
    Vec3 position;
    Vec2 texcoord;
    Vec3 normal;
}Vertex_TEX;

typedef struct Vertex_Particle_
{
    Vec3 position;
    Color3 color;
}Vertex_Particle;

static GLfloat cube_Vertex[] = {
    -1., -1., -1.,
    1., -1., -1.,
    
    1.,  1., -1.,
    -1.,  1., -1.,
    
    -1., -1.,  1.,
    1., -1.,  1.,
    
    1.,  1.,  1.,
    -1.,  1.,  1.
}; // 24

static float cube_Normal[] = {
    0.57    , 0.57      , 0.57,
    0.57    , -0.57     , 0.57,
    -0.57   , -0.57     , 0.57,
    -0.57   , 0.57      , 0.57,
    
    0.57    , 0.57      , -0.57,
    0.57    , -0.57     , -0.57,
    -0.57   , -0.57     , -0.57,
    -0.57   , 0.57      , -0.57
};

static GLushort cube_Index[] = {
    0,2,1,
    0,3,2,
    
    1,2,6,
    6,5,1,
    
    4,5,6,
    6,7,4,
    
    2,3,6,
    6,3,7,
    
    0,7,3,
    0,4,7,
    
    0,1,5,
    0,5,4
}; // 36


static const float rect_TexVertex[] = {
    0.0, 0.0,
    1.0,0.0,
    0.0,1.0,
    1.0,1.0,
};
static const float rect_Vertex[] = {
    -1.0,-1.0,0.0,
    1.0, -1.0,0.0,
    -1.0, 1.0,0.0,
    1.0, 1.0,0.0,
};
static const float rect_Index[] = {
      0,1,2,2,1,3
};

#endif /* defined(__GeoArt__StarStructure__) */