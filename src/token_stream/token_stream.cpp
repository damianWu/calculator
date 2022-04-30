// Copyright [2022] <@damianWu>

#include "token_stream/token_stream.hpp"

#include <iostream>
#include <stdexcept>

#include "calculator/calculator.hpp"
#include "token/token.hpp"

namespace token_stream {

using calculator::END_OF_EXPRESSION;
using calculator::EXIT;
using calculator::TOKEN_KIND_OF_FLOATING_POINT_NUMBER;
using token::Token;

// TODO(@damianWu) Why this works when constructor is marked explicit?
TokenStream::TokenStream() : buffer_{Token{0}}, full_{false} {}

// Give me token from std::cin or the buffer variable;
Token TokenStream::get() {
    if (full_) {
        full_ = false;
        return buffer_;
    }

    // Full token or token fragment
    char token_fragment{};
    std::cin >> token_fragment;

    switch (token_fragment) {
        // Token kind:
        case END_OF_EXPRESSION:
        case EXIT:
        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
        case '%': {
            return Token{token_fragment};
        }
        // Token values:
        case '.':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': {
            // Put back number fragment to the input stream to read it as whole
            std::cin.putback(token_fragment);
            double value{};
            std::cin >> value;
            return Token{TOKEN_KIND_OF_FLOATING_POINT_NUMBER, value};
        }
        default: {
            std::string error_msg{
                "token_stream::TokenStream::get() "
                "throws unknown token exception: "};
            error_msg += token_fragment;
            throw std::runtime_error(error_msg);
        }
    }
}

// Put token to the buffer if empty
void TokenStream::put_back(Token token) {
    if (full_) {
        throw std::runtime_error(
            "token_stream::TokenStream::put_back() "
            "throws: full buffer exception.");
    }
    buffer_ = token;
    full_ = true;
}

}  // namespace token_stream
