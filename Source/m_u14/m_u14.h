// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

template <class T, int   N>
int arraySize(  T (&arr)[N] ) {

   return N;

}
