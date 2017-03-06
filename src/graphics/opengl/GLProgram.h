/*
 * Copyright 2014 Arx Libertatis Team (see the AUTHORS file)
 *
 * This file is part of Arx Libertatis.
 *
 * Arx Libertatis is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Arx Libertatis is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Arx Libertatis.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ARX_GRAPHICS_OPENGL_GLPROGRAM_H
#define ARX_GRAPHICS_OPENGL_GLPROGRAM_H

#include <boost/noncopyable.hpp>
#include <GL/glew.h>

class GLProgram : public boost::noncopyable {
	
public:
	GLProgram();
	~GLProgram();
	
	bool isValid() { return m_isValid; }
	GLint getAttribute(const char * name);
	GLint getUniform(const char * name);
	
	void use();
	
private:
	bool m_isValid;
	GLuint m_program;
};

#endif // ARX_GRAPHICS_OPENGL_GLPROGRAM_H
