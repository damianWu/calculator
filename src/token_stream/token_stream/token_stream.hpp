// Copyright [2022] <@damianWu>

#ifndef SRC_TOKEN_STREAM_TOKEN_STREAM_TOKEN_STREAM_HPP_
#define SRC_TOKEN_STREAM_TOKEN_STREAM_TOKEN_STREAM_HPP_

#include "token/token.hpp"

namespace token_stream {

using token::Token;

class TokenStream {
 public:
    Token get();
    void put_back(Token token);
};

}  // namespace token_stream

#endif  // SRC_TOKEN_STREAM_TOKEN_STREAM_TOKEN_STREAM_HPP_
