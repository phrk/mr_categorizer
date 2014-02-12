/* 
 * File:   WordOccurs.h
 * Author: phrk
 *
 * Created on February 5, 2014, 10:54 AM
 */

#ifndef WORDOCCURS_H
#define	WORDOCCURS_H

#include "mapreduce/core/mapreduce.h"
#include "WordOccurs.pb.h"

class WordOccurs : public EmitType {
public:
	// category / noccurs
	std::tr1::unordered_map<uint64_t, uint64_t> m_occurs;
	
	virtual void restore(const std::string &_dump);
	virtual void dump(std::string &_dump) const;
	virtual ~WordOccurs();
};


#endif	/* WORDOCCURS_H */

