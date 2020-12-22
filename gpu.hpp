/*!
 * @file
 * @brief This file contains class that represents graphic card.
 *
 * @author Tomáš Milet, imilet@fit.vutbr.cz
 */
#pragma once

#include <student/fwd.hpp>
#include <unordered_map>
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <memory>


/**
 * @brief This class represent software GPU
 */
class GPU{
  public:
    GPU();
    virtual ~GPU();

    //buffer object commands
    BufferID  createBuffer           (uint64_t size);
    void      deleteBuffer           (BufferID buffer);
    void      setBufferData          (BufferID buffer,uint64_t offset,uint64_t size,void const* data);
    void      getBufferData          (BufferID buffer,uint64_t offset,uint64_t size,void      * data);
    bool      isBuffer               (BufferID buffer);

    //vertex array object commands (vertex puller)
    ObjectID  createVertexPuller     ();
    void      deleteVertexPuller     (VertexPullerID vao);
    void      setVertexPullerHead    (VertexPullerID vao,uint32_t head,AttributeType type,uint64_t stride,uint64_t offset,BufferID buffer);
    void      setVertexPullerIndexing(VertexPullerID vao,IndexType type,BufferID buffer);
    void      enableVertexPullerHead (VertexPullerID vao,uint32_t head);
    void      disableVertexPullerHead(VertexPullerID vao,uint32_t head);
    void      bindVertexPuller       (VertexPullerID vao);
    void      unbindVertexPuller     ();
    bool      isVertexPuller         (VertexPullerID vao);

    //program object commands
    ProgramID createProgram          ();
    void      deleteProgram          (ProgramID prg);
    void      attachShaders          (ProgramID prg,VertexShader vs,FragmentShader fs);
    void      setVS2FSType           (ProgramID prg,uint32_t attrib,AttributeType type);
    void      useProgram             (ProgramID prg);
    bool      isProgram              (ProgramID prg);
    void      programUniform1f       (ProgramID prg,uint32_t uniformId,float     const&d);
    void      programUniform2f       (ProgramID prg,uint32_t uniformId,glm::vec2 const&d);
    void      programUniform3f       (ProgramID prg,uint32_t uniformId,glm::vec3 const&d);
    void      programUniform4f       (ProgramID prg,uint32_t uniformId,glm::vec4 const&d);
    void      programUniformMatrix4f (ProgramID prg,uint32_t uniformId,glm::mat4 const&d);

    //framebuffer functions
    void      createFramebuffer      (uint32_t width,uint32_t height);
    void      deleteFramebuffer      ();
    void      resizeFramebuffer      (uint32_t width,uint32_t height);
    uint8_t*  getFramebufferColor    ();
    float*    getFramebufferDepth    ();
    uint32_t  getFramebufferWidth    ();
    uint32_t  getFramebufferHeight   ();

    void      clear(float r, float g, float b, float a);
    void      drawTriangles(uint32_t  nofVertices);

    struct processShader {
        FragmentShader PS;
        VertexShader VS;
        Uniforms processShader_buffer;
    };

    struct VertexHeadSettings {
        BufferID buffer;
        size_t offset;
        AttributeType type;
        uint16_t stride;
        bool enabled;
    };

    struct vertex_heads {
        std::array<VertexHeadSettings, 16> destrictors{ 0 };
        BufferID BUFFIND = 0;
        int indextype = 0;
    };

    std::unordered_map<BufferID, std::vector<uint8_t>> buffering;
    std::unordered_map<VertexPullerID, std::unique_ptr<vertex_heads>> vertexpullering;
    std::unordered_map<ProgramID, std::unique_ptr<processShader>> shadering;

    uint8_t* colorPtr = nullptr;
    float* depthPtr = nullptr;
    vertex_heads* BindPtr = nullptr;
    processShader* SHPtr = nullptr;
    uint32_t heights = 0;
    uint32_t widths = 0;
    uint8_t It = 0;
    uint8_t VertexIT = 0;
    uint8_t ProgramIT = 0;

    
};