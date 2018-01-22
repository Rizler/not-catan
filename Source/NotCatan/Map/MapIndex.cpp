// Fill out your copyright notice in the Description page of Project Settings.

#include "MapIndex.h"

FMapIndex::FMapIndex() 
{}

FMapIndex::FMapIndex(int32 row, int32 col) :
	row(row), col(col)
{}

bool FMapIndex::operator==(const FMapIndex& other) const
{
	return row == other.row && col == other.col;
}
