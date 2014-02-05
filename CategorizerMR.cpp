/* 
 * File:   CategorizerMR.cpp
 * Author: phrk
 * 
 * Created on February 4, 2014, 6:42 PM
 */

#include "CategorizerMR.h"

CategorizerMR::CategorizerMR() {
}

void CategorizerMR::map(const InputType* _input) const {
	//std::cout << "___MAP \n";
	//size_t nemits = 0;
	TextParsedInput *text = (TextParsedInput*) _input;
	for (size_t s = 0; s < text->sents.size(); s++)
		for (size_t w = 0; w < text->sents[s].words.size(); w++) {
			WordOccurs* occurs = new WordOccurs;
			occurs->m_occurs[ text->category ] = 1;
			emit(text->sents[s].words[w], occurs);
			//std::cout << "emits: " << ++nemits << std::endl;
		}
}

EmitType* CategorizerMR::reduce(uint64_t _key, EmitType* _a, EmitType* _b) const {
//	delete _b;
//	return _a;
	WordOccurs *a = (WordOccurs*) _a;
	WordOccurs *b = (WordOccurs*) _b;
	std::tr1::unordered_map<uint64_t, uint64_t>::iterator b_it =
			b->m_occurs.begin();
	std::tr1::unordered_map<uint64_t, uint64_t>::iterator b_end =
			b->m_occurs.end();
	while (b_it != b_end) {
		std::tr1::unordered_map<uint64_t, uint64_t>::iterator a_it =
				a->m_occurs.find(b_it->first);
		if (a_it != a->m_occurs.end())
			a_it->second += b_it->second;
		else
			a->m_occurs.insert(std::pair<uint64_t, uint64_t>
						(b_it->first, b_it->second));
		b_it++;
	}
	delete b;
	return a;
}

void CategorizerMR::finilize(EmitType* _occurs) {
	
}

/*
void CategorizerMR::dumpEmit(const EmitType *_occurs, std::string &_dump) const {
	WordOccurs *occurs = (WordOccurs*) _occurs;
	
}*/

EmitType* CategorizerMR::restoreEmit(const std::string &_dump) const {
	WordOccurs *occurs = new WordOccurs;
	occurs->restore(_dump);
	return (EmitType*) occurs;
}

MapReduce* CategorizerMR::create() const {
	return (MapReduce*) new CategorizerMR;
}

CategorizerMR::~CategorizerMR() {
	
}
