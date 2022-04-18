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
        add("mesh", id);
        load("file", id);
        get("mesh", id);

        void add_mesh(int id, mesh mesh_inst);
        // void load_mesh();
        mesh get_mesh(int id);
        void add_shader(int id, shader shader_inst);
        shader get_shader(int id);

    private:
        map<int id, mesh*> mesh;
        map<int id, shader*> shader;
        map<int id - mesh id, mesh> mesh;
        map<int id - shader id, shader> shader;

        // To other place
        map<id, string> id_string;
        map<string, id> string_id;

        resource();
        ~resource();
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
