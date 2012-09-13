#pragma once

#include "BuildSettings.h"
#include <string.h>
#include <sstream>
#include "File/filestream.h"
#include "File/FileMethods.h"
#include "Utils/IPoint.h"
#include "Utils/Color.h"

#ifdef THREADED
#include "boost/thread.hpp"
#endif

namespace utils
{

#ifdef ENGINE_TARGET_WIN32

#ifdef THREADED
extern boost::recursive_mutex lexCastMutex;
#define LEX_CAST_THREAD_LOCK boost::recursive_mutex::scoped_lock lock(lexCastMutex);
#else
#define LEX_CAST_THREAD_LOCK
#endif

#endif

	void GetLocalTime(SYSTEMTIME& stm);
	/// Мультиплатформенный sleep, время в миллисекундах (в тысячных долях)
	void Sleep(unsigned long msec);

	//
	// Вероятно, переводится как "Read `name=value` pair";
	// парсит строку формата `name=value`, записывает имя в name и значение в value.
	// Возвращает true, если строка в нужном формате и false в противном случае.
	//
	bool ReadNvp(const std::string& str, std::string& name, std::string& value);

	template <class Coll>
	inline void tokenize(const std::string& str, Coll &token, const std::string separators = std::string(" /\t:,()"))
	{
		//const string separators(" /\t:,()");
		std::string input(str);
		std::string::size_type idx = 0;
		if ( (idx = input.find_first_not_of(separators))==std::string::npos)
			return;
		input = input.substr(idx);
		while ( (idx = input.find_first_of(separators))!=std::string::npos )
		{
			token.push_back(input.substr(0, idx));
			input = input.substr(idx+1);
			idx = input.find_first_not_of(separators);
			if (idx == std::string::npos)
				break;
			input = input.substr(idx);
		}
		if ( (input.find_first_of(separators)) == std::string::npos ) token.push_back(input);
	}

	inline bool equals(const char * a, const char * b)
	{
		if ( a == NULL || b == NULL ) {
			assert(false);
			return false;
		}
		while(*a == *b) {
			if ( *a == 0 ) return true;
			++a; ++b;
		}
		return false;
	}

	template <class T>
	inline T lexical_cast(const char * str);

	template <class T>
	inline T lexical_cast(const std::string& str) { return lexical_cast<T>(str.c_str()); }

	template <>
	inline float lexical_cast(const char * str)
	{
		float n = 0.0f;
		assert(str != NULL);
		sscanf(str, "%f", &n);
		return n;
	}
	
	template <>
	inline double lexical_cast(const char * str)
	{
		double n = 0.0f;
		assert(str != NULL);
		sscanf(str, "%lf", &n);
		return n;
	}

	template <>
	inline int lexical_cast(const char * str)
	{
		int n = 0;
		assert(str != NULL);
		sscanf(str, "%d", &n);
		return n;
	}
	
	template <>
	inline long lexical_cast(const char * str)
	{
		long n = 0;
		assert(str != NULL);
		sscanf(str, "%ld", &n);
		return n;
	}

	template <>
	inline unsigned char lexical_cast(const char * str)
	{
		int n = 0;
		assert(str != NULL);
		sscanf(str, "%d", &n);
		return (unsigned char)n;
	}

	template <>
	inline bool lexical_cast(const char * str)
	{
		assert(str != NULL);
		if ( equals(str, "true") || equals(str, "1") ) {
			return true;
		}
		return false;
	}

	template <>
	inline __int64 lexical_cast(const char * str)
    {
        __int64 n = 0;
        assert(str != NULL);
		#ifdef ENGINE_TARGET_WIN32
			sscanf(str, "%I64d", &n);
		#else
			sscanf(str, "%lld", &n);
		#endif
        return n;
    }

	template <class T>
	inline std::string lexical_cast(const T& value)
	{
		std::ostringstream ss;
		ss << value;
		return ss.str();
	}

	bool is_char(int code);
	std::string to_char(int code);

	bool AllowAllAccess(const std::string& theFileName);
	std::string RemoveTrailingSlash(const std::string& theDirectory);

#ifdef ENGINE_TARGET_WIN32
	bool CheckForVista();
	bool CheckFor98Mill();
#endif

/*	class tokenizer
	{
		typedef File::stdfile in_stream;
		typedef std::vector<std::string> token_collect;

		in_stream stream;
		std::string in_string;
		token_collect token;

		token_collect::size_type current_token;

	public:

		tokenizer(const std::string& filename)
		{
			stream.open(filename);
			new_line();
		}

		~tokenizer()
		{}

		void new_line()
		{
			current_token = 0;
			token.clear();
			stream.getline(in_string);
			utils::tokenize(in_string, token);
		}

		bool empty()
		{
			return token.empty();
		}

		std::string get_after_command()
		{
			const std::string separators(" /\t:,()");
			std::string input(in_string);
			std::string::size_type idx = 0;
			idx = input.find_first_not_of(separators);
			input = input.substr(idx);
			idx = input.find_first_of(separators);
			input = input.substr(idx+1);
			idx = input.find_first_not_of(separators);
			input = input.substr(idx);
			return input;
		}

		std::string get_token(int i)
		{
			if (i < static_cast<int>(token.size()))
			{
				return token[i];
			}
			else
			{
				return std::string();
			}
		}

		std::string pop_token()
		{
			if (current_token < token.size())
			{
				return token[current_token++];
			}
			else
			{
				return std::string();
			}
		}

		void pop_token(std::string& str)
		{
			str = pop_token();
		}

		void pop_token(int& num)
		{
			sscanf(token[current_token++].c_str(), "%d", &num);
		}

		void pop_token(float& num)
		{
			sscanf(token[current_token++].c_str(), "%f", &num);
		}

		void pop_token(IPoint& point)
		{
			int x, y;
			pop_token(x);
			pop_token(y);
			point = IPoint(x, y);
		}

		void pop_token(IRect& rect)
		{
			int x, y;
			int width, height;
			pop_token(x);
			pop_token(y);
			pop_token(width);
			pop_token(height);
			rect = IRect(x, y, width, height);
		}

	};*/
}

namespace Xml
{
	template <class T>
	inline bool TiXmlQueryAttribute(Xml::TiXmlElement* elem, const std::string& attrName, T& attrValue)
	{
		const char *value = elem->Attribute(attrName.c_str());
		if (value)
		{
			attrValue = utils::lexical_cast<T>(value);
			return true;
		}
		return false;
	}

	template <class T>
	inline bool TiXmlQueryAttribute(rapidxml::xml_node<>* elem, const std::string& attrName, T& attrValue)
	{
		if (elem->first_attribute(attrName.c_str()))
		{
			attrValue = utils::lexical_cast<T>(string(elem->first_attribute(attrName.c_str())->value()));
			return true;
		}
		return false;
	}

	template <>
	inline bool TiXmlQueryAttribute(Xml::TiXmlElement* elem, const std::string& attrName, std::string& attrValue)
	{
		const char *value = elem->Attribute(attrName.c_str());
		if (value)
		{
			attrValue = std::string(value);
			return true;
		}
		return false;
	}

	template <>
	inline bool TiXmlQueryAttribute(rapidxml::xml_node<>* elem, const std::string& attrName, std::string& attrValue)
	{
		if (elem->first_attribute(attrName.c_str()))
		{
			attrValue = elem->first_attribute(attrName.c_str())->value();
			return true;
		}
		return false;
	}

	// Долгоживущий rapidxml::xml_document
	struct RapidXmlDocument
	{
		std::string filename;
		rapidxml::file<char> file;
		rapidxml::xml_document<char> doc;

		RapidXmlDocument(const std::string &name)
			: filename(name)
			, file(filename.c_str())
		{
			doc.parse<rapidxml::parse_default>(file.data());
		}

		void Reload()
		{
			file = rapidxml::file<char>(filename.c_str());
			doc.parse<rapidxml::parse_default>(file.data());
		}

		rapidxml::xml_node<> *first_node()
		{
			return doc.first_node();
		}

		typedef boost::shared_ptr<RapidXmlDocument> HardPtr;
	};

}

#define TiXmlQueryNvpAttribute(elem, attr) Xml::TiXmlQueryAttribute(elem, #attr, attr)

