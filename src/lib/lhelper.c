#include "lhelper.h"
#include "../helper.h"
#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Person create_person_input() {
  Person data;
  GET_INPUT("Enter name: ", data.name);
  GET_INPUT("Enter surname: ", data.surname);
  GET_INPUT("Enter email: ", data.email);
  GET_INPUT("Enter phone number: ", data.phone_number);

  return data;
}
