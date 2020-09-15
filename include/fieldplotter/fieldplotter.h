#pragma once
//this is an edit
/**
 * Header file for libfieldplotter
 * includes Renderer and some library-wide headers from GLM
*/
#define GLEW_STATIC
#include <GL/glew.h>

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_inverse.hpp>

typedef struct Model {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;
} Model;

typedef struct Point {
	float x, y, z;
	Point() : x(0), y(0), z(0) {}
	Point(float x, float y, float z) : x(x), y(y), z(z) {}
} Point;

typedef struct PointCharge {
	Point p;
	float charge;
	PointCharge(Point p, float charge) : p(p), charge(charge) {}
	PointCharge(float x, float y, float z, float charge) : p(Point(x, y, z)), charge(charge) {}
} PointCharge;

typedef struct Vector {
	float i, j, k;	//vector components
	Vector() : i(0), j(0), k(0) {}
	Vector(float i, float j, float k) : i(i), j(j), k(k) {}
} Vector;


/*
 * A vector field class that creates a N*N*N dimensional cube of vectors, each separated by a certain spatial distance
*/
//TODO: Integrate this with computational code
class VectorField {
	private:
		//TODO: Convert spatial and visible separations to a single "separation" value, calculated by the user-inputted scale
		float spatial_separation;
		int dimension;
		int N;
		float* vectors;	//array of vectors
		float* positions; //positions of the lattice
	public:
		VectorField(float separation, int cubic_dimension);
		~VectorField();
		Vector getVector(Point p);	//Return vector at Point p
		Vector getVector(int index);	//Return vector at index of an array
		Point indexCoords(int i, int j, int k);
		void setVector(Vector v);
		void setVectorAt(Point p, float i, float j, float k);
		int getDimension();
		int getAmount();
		void getVectorComponentBuffer(GLuint* tag, int attribute_index);
		void getVectorPositionBuffer(GLuint* tag, int attribute_index);
};

class Camera {
	private:
		float angle;
		float phi;
		float radius;
		glm::vec3 up;
		glm::vec3 cameraPosition;
		glm::vec3 origin;
		glm::mat4 viewMat;
	public:
	Camera(GLfloat roll_speed);
	glm::mat4 getViewMatrix();
	glm::vec3 getPos();
	void moveLinear(float x, float y, float z);
	void scroll(float amount);
	void moveCamera(float dtheta, float dphi);
};

class Renderer {
	private:
		Camera* camera;
		GLuint vertexbuffer;
		GLuint elementbuffer;
		GLuint normalbuffer;
		GLuint vectorfield_position_buffer;
		GLuint vectorfield_component_buffer;
		
		GLuint vao;
		GLuint programID;
		GLuint axisProgramID;
		GLuint mvpID;

		bool glInitialized;
		bool drawFieldLines;
		bool drawEquipotentials;

		glm::mat4 projectionMat;
		glm::mat4 debugModel;
		glm::mat4 viewMat;
		int width;
		int height;

		Model* arrowModel;

		VectorField* vectorfield;		
		inline void initGL();
		inline void drawAxes();

	public:
		Renderer(VectorField* vf, int w, int h);
		~Renderer();
		void render();
		void updateVectorField(VectorField* newVectorField);
		void debugRenderLattice();
		void resizeViewport(int w, int h);
		Camera* getCamera();
};

GLuint loadShadersFromSource(std::string vertex_source, std::string fragment_source);