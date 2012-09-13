/*
 *  ShaderES.h
 *  Engine
 *
 *  Created by Slava on 2/4/11.
 *  Copyright 2011 Playrix Entertainment. All rights reserved.
 *
 */

#pragma once

#import <OpenGLES/ES2/gl.h>

enum ShadingType {
	SHADING_STANDARD,
	SHADING_ADD_COLOR,
	SHADING_NO_ALPHA,
	SHADING_ONLY_ALPHA,
	SHADING_NO_TEXTURE,
	SHADING_FOG,
	SHADING_GLOW,
	SHADING_COUNT
};

enum ShadingUniform {
	UNIFORM_MATRIX = 0,
	UNIFORM_SAMPLER,
	UNIFORM_COUNT
};

//
// Шейдер в OpenGL ES 2.0
//
@interface ShaderES: NSObject {
	GLuint _program;
	int _uniformMatrix;
	int _uniformSampler;
}

@property(readonly, assign) int uniformMatrix;
@property(readonly, assign) int uniformSampler;

/*
 * Инициализация шейдера:
 *  @vFilename - имя файла вертексного шейдера без расширения
 *  @fFilename - имя файла фрагментного шейдера без расширения
 *  @attributes - атрибуты
 */
-(id)initWithVertexFilename:(NSString*)vFilename fragmentFilename:(NSString*)fFilename attributes:(NSArray*)attr;

/*
 * Использовать шейдер (вызывать glUseShader)
 */
-(void)use;

-(void)validate;

@end
