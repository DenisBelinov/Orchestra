#include <iostream>
#include <cstring>

//-
//-
//-
//-
//- To dos:
//		-specific instrument selector - done
//		-fix += so that the orchestra doesnt have more than 40 instruments - done
//		-GO TO GODDAMN BED ;((((((((((((((
//-
//-
//-
//-

class Instrument
{
	char* m_name;
	int m_count;
public:
	//constructors
	Instrument(int count = 1, const char* name = "asd");
	Instrument(const char* name);
	Instrument(const Instrument& other);
	//func
	int getCount() const { return m_count; };
	const char* getName() const { return m_name; };
	void setName(const char*);
	void setCount(int count) { m_count = count; };
	void print(std::ostream& os = std::cout) const;
	//operators
	Instrument& operator=(const Instrument&);
	//destructor
	~Instrument();
};
Instrument::Instrument(int count, const char* name) : m_name(nullptr), m_count(count)
{
	setName(name);
}
Instrument::Instrument(const char* name) : m_name(nullptr), m_count(1)
{
	setName(name);
}
Instrument::Instrument(const Instrument& other) : m_name(nullptr), m_count(other.getCount())
{
	setName(other.getName());
}
void Instrument::setName(const char* name)
{
	if (!name)
	{
		/*delete[] m_name;
		m_name = nullptr;*/
		return;
	}
	delete[] m_name;
	m_name = new char[strlen(name) + 1];
	strcpy(m_name, name);

}

void Instrument::print(std::ostream& os) const
{
	os << "Instrument name: " << getName() << std::endl;
	os << "Instrument count: " << getCount() << std::endl;
}
Instrument& Instrument::operator=(const Instrument& other)
{
	setName(other.getName());
	setCount(other.getCount());
	return *this;
}
Instrument::~Instrument()
{
	delete[] m_name;
}
void copyInstumentArray(Instrument *& dest, const Instrument* source, int size)
{
	if (!source)
	{
		if (!dest)
			delete[] dest;
		dest = nullptr;
		return;
	}
	if (!dest)
		delete[] dest;
	dest = new Instrument[size];
	for (size_t i = 0; i < size; i++)
	{
		dest[i] = source[i];
	}
	return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\
//~~~~~~~~~~~~ ORCHESTRA CLASS ~~~~~~~~~~~~\\
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\

class Orchestra
{
	char* m_name;
	Instrument* m_members;
	int instrumentCount; //not implemented in the class funtionality
public:
	int difInstrumentCount; // should be called m_arraySize, didnt have the energy to change it :(
							//cosntructors
	Orchestra() : m_members(nullptr), instrumentCount(0), difInstrumentCount(0)
	{
		setName("");
	}
	Orchestra(const char* name, const Instrument* members, int size);
	Orchestra(const char* name);
	Orchestra(const Orchestra& other);
	//functions
	//setters/getters
	void setName(const char* name);
	const char* getName() const;
	const Instrument* getMembers() const;
	//other
	int getSpecificInstrumentCount(const char*) const;
	int getInstrumentCount() const;
	void print(std::ostream& os = std::cout) const;
	//operators
	Orchestra& operator=(const Orchestra& other);
	Orchestra& operator+=(const Instrument& inst);

	//destructor
	~Orchestra();
};

//constructors

Orchestra::Orchestra(const char* name, const Instrument* members, int size) : m_name(nullptr), m_members(nullptr)
{
	setName(name);
	copyInstumentArray(m_members, members, size);
	difInstrumentCount = size;
	instrumentCount = getInstrumentCount();
}
Orchestra::Orchestra(const char* name) : instrumentCount(0), difInstrumentCount(0)
{
	setName(name);
}
Orchestra::Orchestra(const Orchestra& other) : m_name(nullptr), difInstrumentCount(other.difInstrumentCount)
{
	this->setName(other.getName());
	copyInstumentArray(m_members, other.getMembers(), other.difInstrumentCount);
	instrumentCount = getInstrumentCount();
}
//functions
//setters/getters
void Orchestra::setName(const char* name)
{
	if (!name)
	{
		//delete[] m_name;
		//m_name = nullptr;
		return;
	}
	if (!m_name)
		delete[] m_name;
	m_name = new char[strlen(name) + 1];
	strcpy(m_name, name);
}
const char* Orchestra::getName() const
{
	return m_name;
}
const Instrument* Orchestra::getMembers() const
{
	return m_members;
}
//other
int Orchestra::getSpecificInstrumentCount(const char* name) const
{
	for (size_t i = 0; i < difInstrumentCount; i++)
	{
		if (!strcmp((m_members + i)->getName(), name))
		{
			return m_members[i].getCount();
		}
	}

}
int Orchestra::getInstrumentCount() const
{
	int count = 0;
	for (size_t i = 0; i < difInstrumentCount; i++)
	{
		count += m_members[i].getCount();
	}
	return count;
}
void Orchestra::print(std::ostream& os) const
{
	os << "Orchestra name: " << getName() << std::endl;
	for (size_t i = 0; i < difInstrumentCount; i++)
	{
		m_members[i].print(os);
	}
	os << "Total Count: " << getInstrumentCount() << std::endl;
}
//operators
Orchestra& Orchestra::operator=(const Orchestra& other)
{
	setName(other.getName());
	copyInstumentArray(m_members, other.getMembers(), other.difInstrumentCount);
	difInstrumentCount = other.difInstrumentCount;
	instrumentCount = getInstrumentCount();
	return *this;
}
Orchestra& Orchestra::operator+=(const Instrument& ints)
{
	for (size_t i = 0; i < difInstrumentCount; i++)
	{
		if (!strcmp((m_members + i)->getName(), ints.getName()))
		{
			if (instrumentCount + ints.getCount() > 40)
			{
				std::cout << "Error, not enough space in orchestra for these instruments" << std::endl;
				return *this;
			}
			(m_members + i)->setCount((m_members + i)->getCount() + ints.getCount());
			return *this;
		}
	}

	Instrument* temp = new Instrument[difInstrumentCount + 1];
	for (size_t i = 0; i < difInstrumentCount; i++)
	{
		temp[i] = m_members[i];
	}
	temp[difInstrumentCount++] = ints;
	delete[] m_members;
	m_members = temp;
	return *this;
}
//destructor
Orchestra::~Orchestra()
{
	delete[] m_name;
	if(!m_members)
		delete[] m_members;
}

int main()
{
	Instrument instr[3] = { ("fleita"), ("kitara"), ("cigulka") };

	Orchestra or1("Orkestyr1", instr, 3);
	Orchestra or2;
	Orchestra or3("Orkestyr2");
	Orchestra or4(or1);

	//or1.print();
	//or2.print();
	//or3.print();
	//or4.print();

	or2 = or1;
	or2 += Instrument(100, "fleita");
	or2.print();
	std::cout << or2.getSpecificInstrumentCount("fleita");
	return 0;
}


/*Problems :
The orchestra destructor on delete[] members
*/
