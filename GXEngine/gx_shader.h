/* -*- c++ -*- */
/////////////////////////////////////////////////////////////////////////////
//
// Shader.h  -- Copyright (c) 2006 David Henry
// last modification: feb. 7, 2006
//
// This code is licenced under the MIT license.
//
// This software is provided "as is" without express or implied
// warranties. You may freely copy and compile this source into
// applications you distribute provided that the copyright text
// below is included in the resulting source code.
//
// Definitions of GLSL shader related classes.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __SHADER_H__
#define __SHADER_H__

#ifdef _WIN32
#define	WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif // _WIN32

#include <GL/glew.h>
#include <GL/glext.h>
#include <stdexcept>
#include <string>

using std::string;

/////////////////////////////////////////////////////////////////////////////
// Shader class diagram:
//
//                +-------- (abs)                   +---------------+
//                |  Shader  |                      | ShaderProgram |
//                +----------+                      +---------------+
//                     ^
//                     |
//          +----------+----------+
//          |                     |
//   +--------------+        +----------------+
//   | VertexShader |        | FragmentShader |
//   +--------------+        +----------------+
//
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//
// class Shader -- GLSL abstract shader object.  Can be a vertex shader
// or a fragment shader.
//
/////////////////////////////////////////////////////////////////////////////

class Shader
{
protected:
  // Constructor
  Shader (const string &filename);

public:
  // Destructor
  virtual ~Shader ();

public:
  // Accessors
  const string &name () const { return _name; }
  const string &code () const { return _code; }
  GLuint handle () const { return _handle; }
  bool fail () const { return (_compiled == GL_FALSE); }

  virtual GLenum shaderType () const = 0;

public:
  // Public interface
  void printInfoLog () const;

protected:
  // Internal functions
  void compile ()
    throw (std::runtime_error);
  void loadShaderFile (const string &filename)
    throw (std::runtime_error);

protected:
  // Member variables
  string _name;
  string _code;
  GLuint _handle;
  GLint _compiled;
};


/////////////////////////////////////////////////////////////////////////////
//
// class VertexShader -- GLSL vertex shader object.
//
/////////////////////////////////////////////////////////////////////////////

class VertexShader : public Shader
{
public:
  // Constructor
  VertexShader (const string &filename);

public:
  // Return the shader enum type
  virtual GLenum shaderType () const {
    if (GLEW_VERSION_2_0)
      return GL_VERTEX_SHADER;
    else
      return GL_VERTEX_SHADER_ARB;
  }
};


/////////////////////////////////////////////////////////////////////////////
//
// class FragmentShader -- GLSL fragment shader object.
//
/////////////////////////////////////////////////////////////////////////////

class FragmentShader : public Shader
{
public:
  // Constructor
  FragmentShader (const string &filename);

public:
  // Return the shader enum type
  virtual GLenum shaderType () const {
    if (GLEW_VERSION_2_0)
      return GL_FRAGMENT_SHADER;
    else
      return GL_FRAGMENT_SHADER_ARB;
  }
};


/////////////////////////////////////////////////////////////////////////////
//
// class ShaderProgram -- GLSL shader program object.
//
/////////////////////////////////////////////////////////////////////////////

class ShaderProgram
{
public:
  // Constructor/destructor
  ShaderProgram (const string &name,
		 const VertexShader &vertexShader,
		 const FragmentShader &fragmentShader);
  ~ShaderProgram ();

public:
  // Public interface
  void use () const;
  void unuse () const;
  void printInfoLog () const;

  // Accessors
  const string &name () const { return _name; }
  GLuint handle () const { return _handle; }
  bool fail () const { return (_linked == GL_FALSE); }

private:
  // Member variables
  string _name;
  GLuint _handle;
  GLint _linked;
};

#endif // __SHADER_H__
