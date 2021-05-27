
#include <stdio.h>


// ensure that files are preloaded or embedded at compile time for emscripten's filesystem
// there's probably a better way to read files (also, they could be hardcoded as cstrings)

// https://stackoverflow.com/a/2912602/12637867
const char* fromFile(const char* filename)
{
	FILE* file = fopen(filename, "r");
	if (file == nullptr) return nullptr;
	
	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	rewind(file);

	char* source = new char[size]; // this is not deleted
	fread(source, sizeof(char), size, file);
	printf("%s\n", source);
	fclose(file);
	return source;
}

void checkShader(GLuint shaderId)
{
	GLint Result = GL_FALSE;
	int InfoLogLength;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		char* errorMsg = new char[InfoLogLength + 1];
		glGetShaderInfoLog(shaderId, InfoLogLength, NULL, errorMsg);
		printf("Shader compilation error\n%s\n", errorMsg);
		delete[] errorMsg;
	}
}