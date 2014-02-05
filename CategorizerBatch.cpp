/* 
 * File:   CategorizerBatch.cpp
 * Author: phrk
 * 
 * Created on February 4, 2014, 6:42 PM
 */

#include "CategorizerBatch.h"

TextParsedInput::TextParsedInput(const std::string &_dump):
	TextParsed(_dump)
{
}

TextParsedInput::~TextParsedInput()
{
}

CategorizerBatch::CategorizerBatch(htCollScannerPtr _scanner):
	m_scanner(_scanner)
{
	next_input = NULL;
	isend = true;
	if (!_scanner->end()) {
		KeyValue cell =_scanner->getNextCell();
		next_input = new TextParsedInput(cell.value);
		isend = false;
	} else
		isend = true;
}

bool CategorizerBatch::end()
{
	return isend;
}

InputType* CategorizerBatch::getNextInput()
{
	if (isend)
		return NULL;
	
	TextParsedInput *ret = next_input;
	
	if (!m_scanner->end()) {
		KeyValue cell = m_scanner->getNextCell();
		next_input = new TextParsedInput(cell.value);
		isend = false;
	} else
		isend = true;
	
	std::cout << "New input\n";
	return (InputType*)ret;
}

CategorizerBatch::~CategorizerBatch()
{
}
