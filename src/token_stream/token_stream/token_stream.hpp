// Copyright [2022] <@damianWu>

#ifndef SRC_TOKEN_STREAM_TOKEN_STREAM_TOKEN_STREAM_HPP_
#define SRC_TOKEN_STREAM_TOKEN_STREAM_TOKEN_STREAM_HPP_

#include "token/token.hpp"

namespace token_stream {

using token::Token;

// Takes input and makes token from it
class TokenStream {
 public:
    TokenStream();

    Token get();
    void put_back(const Token);
    void ignore(const char up_to);

 private:
    Token buffer_;
    bool full_;
};

}  // namespace token_stream

#endif  // SRC_TOKEN_STREAM_TOKEN_STREAM_TOKEN_STREAM_HPP_
