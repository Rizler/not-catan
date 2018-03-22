// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


template<typename T>
class NOTCATAN_API TTwoDArray
{
public:
	
	TTwoDArray() {};
	
	TTwoDArray(int32 rowSize, int32 columnSize)
	{
		resize(rowSize, columnSize);
	}
	
	void resize(int32 rowSize, int32 columnSize)
	{
		m_array.Reset();
		m_array.InsertDefaulted(0, rowSize);
		for (TArray<T>& innerArray : m_array)
		{
			innerArray.AddZeroed(columnSize);
			innerArray.Num();
		}
	}

	int32 getRowLength() const
	{
		return m_array.Num();
	}

	int32 getColumnLength() const
	{
		return m_array[0].Num();
	}

	bool isInBounds(int32 row, int32 col) const
	{
		return (0 <= row && getRowLength() > row && 0 <= col && getColumnLength() > col);
	}

	TArray<T>& operator[](int32 index)
	{
		return m_array[index];
	}

	const TArray<T>& operator[](int32 index) const
	{
		return m_array[index];
	}

private:
	UPROPERTY()
	TArray<TArray<T>> m_array;
};
