#include <node.h>
#include <node_buffer.h>
#include <windows.h>
#include "lib.h"
#include <iostream>

namespace rdrand
{

    using v8::FunctionCallbackInfo;
    using v8::Isolate;
    using v8::Local;
    using v8::Object;
    using v8::String;
    using v8::Number;
    using v8::Value;

    void rand32(const FunctionCallbackInfo<Value> &args)
    {
        uint32_t r;
        Isolate *isolate = args.GetIsolate();
        BOOL success = rdrand32(&r);
        if (!success)
        {
            isolate->ThrowException(String::NewFromUtf8(isolate, "RDRAND instruction failed").ToLocalChecked());
        }
        args.GetReturnValue().Set((double)r);
    }

    void rand53(const FunctionCallbackInfo<Value> &args)
    {
        uint64_t r;
        Isolate *isolate = args.GetIsolate();
        BOOL success = rdrand64(&r);
        if (!success)
        {
            isolate->ThrowException(String::NewFromUtf8(isolate, "RDRAND instruction failed").ToLocalChecked());
        }
        args.GetReturnValue().Set((double)(r / 2048));
    }

    void seed32(const FunctionCallbackInfo<Value> &args)
    {
        uint32_t r;
        Isolate *isolate = args.GetIsolate();
        BOOL success = rdseed32(&r);
        if (!success)
        {
            isolate->ThrowException(String::NewFromUtf8(isolate, "RDSEED instruction failed").ToLocalChecked());
        }
        args.GetReturnValue().Set((double)r);
    }

    void seed53(const FunctionCallbackInfo<Value> &args)
    {
        uint64_t r;
        Isolate *isolate = args.GetIsolate();
        BOOL success = rdseed64(&r);
        if (!success)
        {
            isolate->ThrowException(String::NewFromUtf8(isolate, "RDSEED instruction failed").ToLocalChecked());
            return;
        }
        args.GetReturnValue().Set((double)(r / 2048));
    }

    void rand64b(const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();
        if (args.Length() < 1)
        {
            isolate->ThrowException(String::NewFromUtf8(isolate, "Must provide number of bytes as an argument").ToLocalChecked());
            return;
        }

        if (!args[0]->IsNumber())
        {
            isolate->ThrowException(String::NewFromUtf8(isolate, "Number of bytes must be a number").ToLocalChecked());
            return;
        }
        double arg1 = args[0].As<Number>()->Value();

        if (arg1 > (double)0xFFFFFFFF || arg1 < (double)1)
        {
            isolate->ThrowException(String::NewFromUtf8(isolate, "Number of bytes must be <= 4294967295 and >= 1").ToLocalChecked());
            return;
        }
        int amount = (int)arg1;
        unsigned char* dest = new unsigned char[amount];
        int success = rdrand_get_bytes(dest, amount);
        if (!success)
        {
            isolate->ThrowException(String::NewFromUtf8(isolate, "RDRAND instruction failed").ToLocalChecked());
            return;
        }
        args.GetReturnValue().Set(node::Buffer::Copy(isolate,
                                                     (const char *)dest,
                                                     amount)
                                      .ToLocalChecked());
        delete dest;
    }

    void seed64b(const FunctionCallbackInfo<Value> &args)
    {
        Isolate *isolate = args.GetIsolate();
        if (args.Length() < 1)
        {
            isolate->ThrowException(String::NewFromUtf8(isolate, "Must provide number of bytes as an argument").ToLocalChecked());
            return;
        }

        if (!args[0]->IsNumber())
        {
            isolate->ThrowException(String::NewFromUtf8(isolate, "Number of bytes must be a number").ToLocalChecked());
            return;
        }
        double arg1 = args[0].As<Number>()->Value();

        if (arg1 > (double)0xFFFFFFFF || arg1 < (double)1)
        {
            isolate->ThrowException(String::NewFromUtf8(isolate, "Number of bytes must be <= 4294967295 and >= 1").ToLocalChecked());
            return;
        }
        int amount = (int)arg1;
        unsigned char* dest = new unsigned char[amount];
        int success = rdseed_get_bytes(dest, amount);
        if (!success)
        {
            isolate->ThrowException(String::NewFromUtf8(isolate, "RDRAND instruction failed").ToLocalChecked());
            return;
        }
        args.GetReturnValue().Set(node::Buffer::Copy(isolate,
                                                     (const char *)dest,
                                                     amount)
                                      .ToLocalChecked());
        delete dest;
    }

    void rand64s(const FunctionCallbackInfo<Value> &args)
    {
        uint64_t r;
        Isolate *isolate = args.GetIsolate();
        BOOL success = rdrand64(&r);
        if (!success)
        {
            isolate->ThrowException(String::NewFromUtf8(isolate, "RDRAND instruction failed").ToLocalChecked());
        }
        args.GetReturnValue().Set(
            String::NewFromUtf8(isolate, std::to_string(r).c_str()).ToLocalChecked());
    }

    void seed64s(const FunctionCallbackInfo<Value> &args)
    {
        uint64_t r;
        Isolate *isolate = args.GetIsolate();
        BOOL success = rdseed64(&r);
        if (!success)
        {
            isolate->ThrowException(String::NewFromUtf8(isolate, "RDSEED instruction failed").ToLocalChecked());
        }
        args.GetReturnValue().Set(
            String::NewFromUtf8(isolate, std::to_string(r).c_str()).ToLocalChecked());
    }

    void rdrand_not_supported(const FunctionCallbackInfo<Value> &args)
    {
        args.GetReturnValue().Set(true);
    }

    void Initialize(Local<Object> exports)
    {
        if (supports_rdrand())
        {
            NODE_SET_METHOD(exports, "rand32", rand32);
            NODE_SET_METHOD(exports, "rand53", rand53);
            NODE_SET_METHOD(exports, "seed32", seed32);
            NODE_SET_METHOD(exports, "seed53", seed53);
            NODE_SET_METHOD(exports, "rand64b", rand64b);
            NODE_SET_METHOD(exports, "seed64b", seed64b);
            NODE_SET_METHOD(exports, "rdrandBytes", rand64s);
            NODE_SET_METHOD(exports, "rdseedBytes", seed64s);
        }
        else
        {
            NODE_SET_METHOD(exports, "rdrand_not_supported", rdrand_not_supported);
        }
    }

    NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

}