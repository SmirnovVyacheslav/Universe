// Copyright: (C) 2021-2022 Vyacheslav Smirnov. All rights reserved.

#pragma once
#ifndef RESOURCE_H
#define RESOURCE_H


namespace engine
{
    class resource;

    static const resource inst;

    class resource
    {
    public:
        set(resource_type, resource_id, object_id);
        // _load("file", id);
        get(resource_type, object_id);

        // enum
        // "mesh" - 1
        // "shader" - 2

        //void add_mesh(int id, mesh mesh_inst);
        // void load_mesh();
        //mesh get_mesh(int id);
        //void add_shader(int id, shader shader_inst);
        //shader get_shader(int id);

    private:
        map<resource_type, map<int id, recource*>> resources_map;
        map<int object_id, map<resource_type, resource_id>> object_map;
        //map<int id, mesh*> mesh;
        //map<int id, shader*> shader;
        //map<int id - mesh id, mesh> mesh;
        //map<int id - shader id, shader> shader;

        // To other place
        map<id, string> id_string;
        map<string, id> string_id;

        resource();
        ~resource();
    };

    class mesh_resource
    {

    };

    // To cpp
    resource resource::inst = resource();


    // To core types
    struct mesh
    {
        arr vector_3d;
    };
    void create_mesh();

    struct vertex
    {

    };

    struct vector_3d
    {

    };


    // To object ids
    class object
    {
        int id;
        create(string name);
    };
}
#endif
