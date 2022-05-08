// Copyright [2022] <@damianWu>

#ifndef SRC_TOKEN_STREAM_TOKEN_STREAM_TOKEN_STREAM_HPP_
#define SRC_TOKEN_STREAM_TOKEN_STREAM_TOKEN_STREAM_HPP_

#include <string>

#include "token/token.hpp"

namespace token_stream {

using token::Token;

// Takes input and makes token from it
class TokenStream {
 public:
    TokenStream();

    Token get();
    void put_back(Token);
    void ignore(char);

 private:
    Token buffer_;
    bool full_;
};

void read_word(std::string* s);
Token give_appropriate_token(const std::string& word);

}  // namespace token_stream

#endif  // SRC_TOKEN_STREAM_TOKEN_STREAM_TOKEN_STREAM_HPP_
