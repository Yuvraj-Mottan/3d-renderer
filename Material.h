#pragma once
class Material {
public:
	Material(const char* filename);
	void use(int unit);
	~Material();
private:
	unsigned int texture;
};