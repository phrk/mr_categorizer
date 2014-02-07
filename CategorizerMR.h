/* 
 * File:   CategorizerMR.h
 * Author: phrk
 *
 * Created on February 4, 2014, 6:42 PM
 */

#ifndef CATEGORIZERMR_H
#define	CATEGORIZERMR_H

#include "WordOccurs.h"

#include "../tetramorph/mapreduce/core/mapreduce.h"

//#include "CategorizerBatch.h"

#include <tr1/unordered_map>

#include "../hcrawler/wwwht/TextParsed.h"

class TextParsedInput : public InputType, public TextParsed {
public:
	TextParsedInput(const std::string &_dump);
	virtual ~TextParsedInput();
};

class CategorizerMR : public MapReduce {
public:
	CategorizerMR();
	
	virtual void map(const InputType* object) const;
	virtual EmitType* reduce(uint64_t key, EmitType* a, EmitType* b) const;
	virtual void finilize(EmitType*);

	//virtual void dumpEmit(const EmitType *_emit, std::string &_dump) const;
	virtual EmitType* restoreEmit(const std::string &_dump) const;

	virtual MapReduce *create() const;
	virtual ~CategorizerMR();
	
private:

};

#endif	/* CATEGORIZERMR_H */

