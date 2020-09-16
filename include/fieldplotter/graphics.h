#pragma once
#include <fieldplotter/commonheaders.h>
//#include <fieldplotter/vectors.h>

GLuint loadShadersFromSource(std::string vertex_source, std::string fragment_source);


typedef struct Model {
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;
} Model;


void loadArrowModel(std::vector<glm::vec3>& positions, std::vector<glm::vec3>& normals, std::vector<unsigned int>& indices);

enum VectorField_GraphicBuffers {
	FP_VERTICES=0,
	FP_NORMALS,
	FP_POSITION,
	FP_COMPONENTS,
	FP_ELEMENTS
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

class Plottable;
class Scene {
	private:
		Camera* camera;
		GLuint vao;
		
        GLuint sceneMatrices;
		glm::mat4 projectionMat;
		glm::mat4 viewMat;
		
        int width;
		int height;
        std::vector<Plottable*> plottables;	
		inline void initGL();
	public:
		Scene(int width, int height);
		//Scene(VectorField* vf, int w, int h);
		~Scene();
		void render();
		void resizeViewport(int w, int h);
		void addPlottable(Plottable* plottable);
		GLuint getSceneMatrices();
		Camera* getCamera();
};

class Plottable {   //a VectorField is a Plottable. so is a point charge and an equipotential surface
	protected:
	Scene* parent;
    GLuint* buffers;
    int n_buffers;
    GLuint programID;
	glm::mat4 modelMatrix;
    virtual void initGL()=0;
    public:
	virtual void draw()=0;
	virtual void setParent(Scene* parent)=0;
};

