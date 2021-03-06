#include "Sprite.h"
#include "Vertex.h"

#include <cstddef>

Sprite::Sprite()
{
	_vboID = 0;
}

Sprite::~Sprite()
{
	if (_vboID) {
		glDeleteBuffers(1, &_vboID);
	}
}

void Sprite::init(float x, float y, float width, float height) {
	_x = x;
	_y = y;
	_width = width;
	_height = height;

	if (!_vboID) {
		glGenBuffers(1, &_vboID);
	}

	Vertex vertexData[6];

	// First Triangle
	vertexData[0].setPosition(x + width, y + height);
	vertexData[0].SetUV(1.0f, 1.0f);

	vertexData[1].setPosition(x, y + height);
	vertexData[1].SetUV(0.0f, 1.0f);

	vertexData[2].setPosition(x, y);
	vertexData[2].SetUV(0.0f, 0.0f);

	// Second Triangle
	vertexData[3].setPosition(x, y);
	vertexData[3].SetUV(0.0f, 0.0f);
	
	vertexData[4].setPosition(x + width, y);
	vertexData[4].SetUV(1.0f, 0.0f);
	
	vertexData[5].setPosition(x + width, y + height);
	vertexData[5].SetUV(1.0f, 1.0f);

	for (int i = 0; i < 6; i++) {
		vertexData[i].setColor(255, 0, 255, 255);
	}

	vertexData[4].setColor(0, 0, 255, 255);
	vertexData[4].setColor(0, 255, 0, 255);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Sprite::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// this is the position attribute pointer
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));

	// color attribute pointer
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, color));

	//UV attribute pointer
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}