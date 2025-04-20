#include "Arduino.h"
#include "Stack.h"

Stack::Stack(){
  _top = -1;
  _capacity = 20;
  _stack[_capacity];
}

Stack::Stack(uint8_t size){
  _top = -1;
  _capacity = size;
  _stack[_capacity];
}

void Stack::push(float n){
  _stack[++_top] = n;
}

float Stack::pop(){
  return _stack[_top--];
}

float Stack::peek(){
  return _stack[_top];
}

boolean Stack::isFull(){
 return _top == _capacity-1;
}

boolean Stack::isEmpty(){
  return _top == -1;
}