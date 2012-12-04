// filter.cpp
//
// Copyright (c) 2008-2009
// Steven Watanabe
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <string>
#include <cstdio>
#include <cstring>

const char* search("template_profiler");

#if defined(_MSC_VER)
    const char* back_trace_search("see reference to");
#elif defined(__GNUC__)
    const char* back_trace_search("instantiated from");
#else
    #error only Microsoft and gcc are supported.
#endif

void copy_flat_only() {
    std::string buffer;
    int ch;
    int pos = 0;
    bool matched = false;
    int counter = 0;
    while((ch = std::getchar()) != EOF) {
        buffer.push_back(static_cast<char>(ch));
        if(ch == '\n') {
            if(matched) {
                for(std::size_t i = 0; i < buffer.size(); ++i) {
                    std::putchar(buffer[i]);
                }
                ++counter;
#ifdef _MSC_VER
                if(counter % 400 == 0) {
                    std::fprintf(stderr, "On Instantiation %d\n", counter/4);
                }
#else
                if(counter % 200 == 0) {
                    std::fprintf(stderr, "On Instantiation %d\n", counter/2);
                }
#endif
            }
            buffer.clear();
            matched = false;
        }
        if(ch == search[pos]) {
            ++pos;
            if(search[pos] == '\0') {
                matched = true;
            }
        } else {
            pos = 0;
        }
    }
}

void copy_call_graph() {
#if defined(_MSC_VER) && 0
    std::string buffer;
    int ch;
    int pos = 0;
    bool matched = false;
    int counter = 0;
    while((ch = std::getchar()) != EOF) {
        buffer.push_back(static_cast<char>(ch));
        if(ch == '\n') {
            if(matched) {
                for(std::size_t i = 0; i < buffer.size(); ++i) {
                    std::putchar(buffer[i]);
                }
                if(++counter % 200 == 0) {
                    std::fprintf(stderr, "On Instantiation %d\n", counter/2);
                }
                buffer.clear();
                matched = false;
                // process instantiation back-trace
                pos = 0;
                while((ch = std::getchar()) != EOF) {
                    if(ch == ' ') {
                        buffer.push_back(static_cast<char>(ch));
                        while((ch = std::getchar()) != EOF) {
                            buffer.push_back(static_cast<char>(ch));
                            if(ch == '\n') {
                                if(matched) {
                                    for(std::size_t i = 0; i < buffer.size(); ++i) {
                                        std::putchar(buffer[i]);
                                    }
                                }
                                buffer.clear();
                                matched = false;
                                pos = 0;
                                break;
                            }
                            if(ch == back_trace_search[pos]) {
                                ++pos;
                                if(back_trace_search[pos] == '\0') {
                                    matched = true;
                                }
                            } else {
                                pos = 0;
                            }
                        }
                    } else {
                        std::ungetc(ch, stdin);
                        break;
                    }
                }
            }
            buffer.clear();
            matched = false;
            pos = 0;
        }
        if(ch == search[pos]) {
            ++pos;
            if(search[pos] == '\0') {
                matched = true;
            }
        } else {
            pos = 0;
        }
    }
#elif defined(__GNUC__) || 1
    // trying to figure out what we should copy is too hard.
    int ch;
    while((ch = std::getchar()) != EOF) {
        std::putchar(ch);
    }
#else
    #error Unknown compiler
#endif
}

int main(int argc, char** argv)
{
  copy_call_graph();
}
