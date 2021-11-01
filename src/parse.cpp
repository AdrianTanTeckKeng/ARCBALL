#include "parse.h"

Object load_object(std::string name, const char* filename){
    Object _object;

    std::string directory = "data/";
    directory += filename;
    const char *fileLocation = directory.c_str();

    // Opening file
    std::ifstream file(fileLocation);
    if (!file.is_open())
    {
        std::cout << "error: " << filename << " does not exist." << std::endl;
        exit(1);
    }


    // Parsing data
    // Temporary data to store components of vertices, normals, and the indices in which the faces and its normals can be constructed from the vertices and normals.

    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<int> faces;
    std::vector<int> normalIdx;

    std::string line;
    int numOfVertices = 0;
    int numOfFaces = 0;
    int numOfNorms = 0;
    while(std::getline(file, line)){
        // Initialize a stringstream to parse the contents of the line.
        std::stringstream ss(line);

        // Declare variable to store the string, int, and double values.
        std::string type;

        // Parse string
        ss >> type;
        if(ss.fail())
        {
            std::cout << "Error: unable to parse line." << std::endl;
        }

        if (type == "v")
        {
            float x0, x1, x2;
            ss >> x0 >> x1 >> x2;
            numOfVertices += 1;
            vertices.push_back(x0);
            vertices.push_back(x1);
            vertices.push_back(x2);
        }
        else if (type == "vn")
        {
            float x0, x1, x2;
            ss >> x0 >> x1 >> x2;
            numOfNorms += 1;
            normals.push_back(x0);
            normals.push_back(x1);
            normals.push_back(x2);
        }
        else
        {
            std::string tmp1, tmp2, tmp3;
            ss >> tmp1 >> tmp2 >> tmp3;
            std::string regex_str = "//"; 
            auto tokens_tmp1 = split(tmp1, regex_str);
            auto tokens_tmp2 = split(tmp2, regex_str);
            auto tokens_tmp3 = split(tmp3, regex_str);
            
            
            faces.push_back(stoi(tokens_tmp1[0]));
            faces.push_back(stoi(tokens_tmp2[0]));
            faces.push_back(stoi(tokens_tmp3[0]));
            normalIdx.push_back(stoi(tokens_tmp1[1]));
            normalIdx.push_back(stoi(tokens_tmp2[1]));
            normalIdx.push_back(stoi(tokens_tmp3[1]));
            numOfFaces += 1;
        }
    }

    // Now we store all the information in struct
    // First store the name
    _object.name = name;

    // Store the components of the vertices that made up faces in vertex buffer
    for(int i=0; i<numOfFaces; i++)
    {
        int f0 = faces[3*i];
        int f1 = faces[3*i+1];
        int f2 = faces[3*i+2];
        Triple _tmp0;
        _tmp0.x = vertices[3*(f0-1)];
        _tmp0.y = vertices[3*(f0-1) + 1];
        _tmp0.z = vertices[3*(f0-1) + 2];
        _object.vertex_buffer.push_back(_tmp0);

        Triple _tmp1;
        _tmp1.x = vertices[3*(f1-1)];
        _tmp1.y = vertices[3*(f1-1) + 1];
        _tmp1.z = vertices[3*(f1-1) + 2];
        _object.vertex_buffer.push_back(_tmp1);

        Triple _tmp2;
        _tmp2.x = vertices[3*(f2-1)];
        _tmp2.y = vertices[3*(f2-1) + 1];
        _tmp2.z = vertices[3*(f2-1) + 2];
        _object.vertex_buffer.push_back(_tmp2);
    }

    // Store the components of the normals of the faces in normal buffer
    for(int i=0; i<numOfFaces; i++)
    {
        int n0 = normalIdx[3*i];
        int n1 = normalIdx[3*i+1];
        int n2 = normalIdx[3*i+2];

        Triple _tmp0;
        _tmp0.x = normals[3*(n0-1)];
        _tmp0.y = normals[3*(n0-1) + 1];
        _tmp0.z = normals[3*(n0-1) + 2];
        _object.normal_buffer.push_back(_tmp0);

        Triple _tmp1;
        _tmp1.x = normals[3*(n1-1)];
        _tmp1.y = normals[3*(n1-1) + 1];
        _tmp1.z = normals[3*(n1-1) + 2];
        _object.normal_buffer.push_back(_tmp1);

        Triple _tmp2;
        _tmp2.x = normals[3*(n2-1)];
        _tmp2.y = normals[3*(n2-1) + 1];
        _tmp2.z = normals[3*(n2-1) + 2];
        _object.normal_buffer.push_back(_tmp2);
    }

    return _object;
}

void parse(const char* filename)
{
    std::cout << "Loading file" << filename << std::endl;

    // Opening file
    std::ifstream file(filename);

    if(!file.is_open()){
        std::cout << "error: " << filename << " does not exist." << std::endl;
        exit(1);
    }

    // 1. Reading in camera configurations. Pretty much have to hardcore these lines
    std::string line;
    std::string dummy;

    // This reads camera:
    std::getline(file, line);

    // Get position
    std::getline(file, line);
    std::stringstream ss(line);
    ss >> dummy >> scene_camera.cam_position[0] >> scene_camera.cam_position[1] >> scene_camera.cam_position[2];

    // Get orientation
    float _angle;
    std::getline(file, line);
    ss.str("");
    ss.clear();
    ss << line;
    
    ss >> dummy >> scene_camera.cam_orientation_axis[0] >> scene_camera.cam_orientation_axis[1] >> scene_camera.cam_orientation_axis[2] >> _angle;

    scene_camera.cam_orientation_angle = rad2deg(_angle);

    // Get near, far, left, right, top, bottom
    std::getline(file, line);
    ss.str("");
    ss.clear();
    ss << line;
    ss >> dummy >> scene_camera.near_param;

    std::getline(file, line);
    ss.str("");
    ss.clear();
    ss << line;
    ss >> dummy >> scene_camera.far_param;

    std::getline(file, line);
    ss.str("");
    ss.clear();
    ss << line;
    ss >> dummy >> scene_camera.left_param;

    std::getline(file, line);
    ss.str("");
    ss.clear();
    ss << line;
    ss >> dummy >> scene_camera.right_param;

    std::getline(file, line);
    ss.str("");
    ss.clear();
    ss << line;
    ss >> dummy >> scene_camera.top_param;

    std::getline(file, line);
    ss.str("");
    ss.clear();
    ss << line;
    ss >> dummy >> scene_camera.bottom_param;

    std::getline(file, line); // Clear the white space

    // 2. Storing lightings
    while(std::getline(file, line)){
        std::stringstream tmp_ss(line);
        std::string dummy;
        tmp_ss >> dummy;
        if(dummy!="light"){
            break;
        }
        float x0, x1, x2, r0, r1, r2, k;
        tmp_ss >> x0 >> x1 >> x2 >> dummy >> r0 >> r1 >> r2 >> dummy >> k;
        Point_Light _light;
        _light.position[0] = x0;
        _light.position[1] = x1;
        _light.position[2] = x2;
        _light.position[3] = 1.;

        _light.color[0] = r0;
        _light.color[1] = r1;
        _light.color[2] = r2;
        _light.attenuation_k = k;
        lights.push_back(_light);
    }

    // 3. Storing original objects in temp vector 
    std::vector<Object> _tmpObjects;

    while(std::getline(file, line))
    {
        std::stringstream tmp_ss(line);
        std::string type, objectFileName;
        tmp_ss >> type;

        if(type == ""){
            break;
        }
        
        tmp_ss >> objectFileName;
        //std::cout << "Getting object " << type << " with file name: " << objectFileName << std::endl;       
        _tmpObjects.push_back(load_object(type, objectFileName.c_str()));
    }

    // 4. Reading materials and transformations
    while(std::getline(file, line))
    {

        // Now we will store the objects in Objects

        // First get the name
        Object _object;
        std::stringstream ss(line);
        std::string name;
        ss >> name;
        _object.name = name;

        // Using the name, we can go through all the list of objects and find the correct object and copy over the vertex_buffer and normal_buffer

        bool flag = false;
        for(int i=0; i<_tmpObjects.size(); i++)
        {
            if(_tmpObjects[i].name == _object.name)
            {
                _object.vertex_buffer = _tmpObjects[i].vertex_buffer;
                _object.normal_buffer = _tmpObjects[i].normal_buffer;
                flag = true;
            }

        }

        if(!flag)
        {
            std::cout << "Couldnt find the object to copy data " << std::endl;
            exit(1);
        }

        
        while(std::getline(file, line))
        {
            std::stringstream ss(line);
            std::string type;
            ss >> type;
            if(type == "")
            {
                break;
            }

            // First store information on ambient, specular, diffuse and shininess.


            // ambient
            if(type == "ambient")
            {
                ss >> _object.ambient_reflect[0] >> _object.ambient_reflect[1] >> _object.ambient_reflect[2];
                continue;
            }

            // diffuse
            if(type == "diffuse")
            {
                ss >> _object.diffuse_reflect[0] >> _object.diffuse_reflect[1] >> _object.diffuse_reflect[2];
                continue;
            }

            // specular
            if(type == "specular")
            {
                ss >> _object.specular_reflect[0] >> _object.specular_reflect[1] >> _object.specular_reflect[2];
                continue;
            }

            // shininess
            if(type == "shininess")
            {
                ss >> _object.shininess;
                continue;
            }

            // Next store information on transformations. I will do a very lazy way of storing each transformation using the original structure to save effort.


            if(type=="t")
            {
                Transforms _transform;
                _transform.type = type;
                float x0, x1, x2;
                ss >> x0 >> x1 >> x2;
                _transform.translation[0] = x0;
                _transform.translation[1] = x1;
                _transform.translation[2] = x2;
                _object.transform_sets.push_back(_transform);
            }

            else if(type=="r")
            {
                Transforms _transform;
                _transform.type = type;
                float x0, x1, x2, x3;
                ss >> x0 >> x1 >> x2 >> x3;
                _transform.rotation[0] = x0;
                _transform.rotation[1] = x1;
                _transform.rotation[2] = x2;
                _transform.rotation_angle = rad2deg(x3);
                _object.transform_sets.push_back(_transform);
            }

            else if(type=="s")
            {
                Transforms _transform;
                _transform.type = type;
                float x0, x1, x2;
                ss >> x0 >> x1 >> x2;
                _transform.scaling[0] = x0;
                _transform.scaling[1] = x1;
                _transform.scaling[2] = x2;
                _object.transform_sets.push_back(_transform);
            }

        }
        objects.push_back(_object);
    }
    file.close();
}