/* 
 * File:   CategorizerBatch.h
 * Author: phrk
 *
 * Created on February 4, 2014, 6:42 PM
 */

#ifndef CATEGORIZERBATCH_H
#define	CATEGORIZERBATCH_H

#include "mapreduce/core/mapreduce.h"

#include "htdba/htCollScanner.h"

#include "CategorizerMR.h"

class CategorizerBatch : public BatchAccessor {
	htCollScannerPtr m_scanner;
	bool isend;
	TextParsedInput *next_input;
public:
	CategorizerBatch(htCollScannerPtr _scanner);
	virtual bool end();
	virtual InputType *getNextInput();
	virtual ~CategorizerBatch();
};



#endif	/* CATEGORIZERBATCH_H */

