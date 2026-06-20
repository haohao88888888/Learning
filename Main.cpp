//#include <iostream>
//
//class Log
//{
//public:
//	const int LogLevelError = 0;
//	const int LogLevelWarning = 1;
//	const int LogLevelInfo = 2;
//
//private:
//	int m_LogLevel = LogLevelInfo;
//
//public:
//	void SetLevel(int level)
//	{
//		m_LogLevel = level;
//	}
//
//	void Error(const char* message)
//	{
//		if (m_LogLevel >= LogLevelError)
//			std::cout << "[ERROR]:" << message << std::endl;
//	}
//
//	void Warn(const char* message)
//	{
//		if (m_LogLevel >= LogLevelWarning)
//			std::cout << "[Warning]:" << message << std::endl;
//	}
//
//	void Info(const char* message)
//	{
//		if (m_LogLevel >= LogLevelInfo)
//			std::cout << "[INFO]:" << message << std::endl;
//	}
//};
//
//int main()
//{
//	Log log;
//	log.SetLevel(log.LogLevelWarning);
//	log.Warn("Hello");
//	std::cin.get();
//}
//
//#include <iostream>
//
//class Entity
//{
//public:
//	float X, Y;
//	Entity()
//	{
//		X = 0.0f;
//		Y = 0.0f;
//		std::cout << "Created Entity" << std::endl;
//	}
//
//	Entity(float x, float y)
//	{
//		X = x;
//		Y = y;
//	}
//
//	~Entity()
//	{
//		std::cout << "Destroyed Entity" << std::endl;
//	}
//
//	void Print()
//	{
//		std::cout << X << ", " << Y << std::endl;
//	}
//};
//
//void Function()
//{
//	Entity e;
//	e.Print();
//}
//  
//int main()
//{
//	Function();
//
//	std::cin.get();
//}
//
//#include <iostream>
//#include <string.h>
//
//class Entity
//{
//private:
//	int a;
//	std::string m_Name = "wh";
//public:
//	const std::string& GetName() const
//	{
//		return m_Name;
//	}
//};
//
//void Getname(const std::string e)
//{
//
//}
//
//int main()
//{
//	int x = 8;
//	auto f = [=]() mutable
//	{
//		x++;
//		std::cout << x << std::endl;
//	};
//
//	f();
//
//	std::cout << x << std::endl;
//
//	std::cin.get();
//}
//
//#include <iostream>
//#include <string.h>
//
//class Entity
//{
//private:
//	std::string m_Name;
//	int m_age;
//public:
//	Entity(const std::string& name)
//		: m_Name(name), m_age(-1){ }
//
//	Entity(int age)
//		: m_Name("Unknown"), m_age(m_age) { }
//};
//
//int main()
//{
//	Entity a("wh");
//	Entity b(d22);
//	std::cin.get();
//}
//
//#include <iostream>
//#include <string>
//#include <memory>
//
//class Entity
//{
//public:
//	Entity()
//	{
//		std::cout << "Create Entity!" << std::endl;
//	}
//
//	~Entity()
//	{
//		std::cout << "Destoryed Entity!" << std::endl;
//	}
//
//	void Print() {};
//
//};
//
//int main()
//{
//	{
//		std::unique_ptr<Entity> entity(new Entity());
//		std::unique_ptr<Entity> entity = std::make_unique<Entity>();
//
//		entity->Print();
//	}
//
//
//	std::cin.get();
//}
//
//#include <iostream>
//#include <string>
//
//class String
//{
//private:
//	char* m_Buffer;
//	unsigned int m_Size;
//public:
//	String(const char* string)
//	{ 
//		m_Size = strlen(string);
//		m_Buffer = new char[m_Size + 1];
//		memcpy(m_Buffer, string, m_Size);
//		m_Buffer[m_Size] = 0;
//	}
//
//	String(const String& other)
//		: m_Size(other.m_Size)
//	{
//		m_Buffer = new char[m_Size + 1];
//		memcpy(m_Buffer, other.m_Buffer, m_Size + 1);
//	}
//
//	~String()
//	{
//		delete[] m_Buffer;
//	}
//
//	char& operator[](unsigned int index)
//	{
//		return m_Buffer[index];
//	}
//
//	friend std::ostream& operator<<(std::ostream& stream, const String& string);
//};
//
//std::ostream& operator<<(std::ostream& stream, const String& string)
//{
//	当遇到打印 String 对象时，请把它内部的 m_Buffer（原生字符串指针）丢给系统的 stream 去打印
//	stream << string.m_Buffer;
//	return stream;
//}
//
//在基础时刻要通过const引用来传递对象
//void PrintString(const String& string)
//{
//	std::cout << string << std::endl;
//}
//
//int main()
//{
//	String string = "wh";
//	String second = string;
//
//	second[1] = 'A';
//
//	PrintString(string);
//	PrintString(second);
//
//	std::cin.get();
//}
//
//#include <iostream>
//#include <string>
//
//class Entity
//{
//public:
//	int x;
//public:
//	void Print() const
//	{
//		std::cout << "Hello!" << std::endl;
//	}
//};
//
//class ScopedPtr
//{
//private:
//	Entity* m_obj;
//public:
//	ScopedPtr(Entity* entity)
//		:m_obj(entity)
//	{
//
//	}
//
//	~ScopedPtr()
//	{
//		delete m_obj;
//	}
//
//	Entity* operator->()
//	{
//		return m_obj;
//	}
//
//	const Entity* operator->() const
//	{
//		return m_obj;
//	}
//};
//
//int main()
//{
//	const ScopedPtr entity = new Entity;
//	entity->Print();
//
//	std::cin.get();
//}
//
//#include <iostream>
//#include <string>
//#include <vector>
//
//struct Vertex
//{
//	float x, y, z;
//
//	Vertex(float x, float y, float z)
//		: x(x), y(y), z(z)
//	{
//	}
//
//	Vertex(const Vertex& vertex)
//	{
//		std::cout << "Copyed" << std::endl;
//	}
//};
//
//int main()
//{
//	std::vector<Vertex> vertices;
//	vertices.reserve(3);
//	vertices.emplace_back(4, 5, 6);
// 
//	std::cin.get();
//}
//
//#include <iostream>
//#include <string>
//#include <array>
//
//template<typename T>
//void Print(T value)
//{
//	std::cout << value << std::endl;
//}
//
//template<typename T, int N>
//class Array
//{
//private:
//	T m_Array[N];
//public:
//	int GetSize() const { return N; }
//};
//
//template<std::size_t N>
//void PrintArray (const std::array<int, N>& data)
//{
//}
//
//int main()
//{
//	Print(5);
//	Array<int, 5> array;
//	std::cout << array.GetSize() << std::endl;
//
//	std::array<int, 5> data;
//	PrintArray(data);
//	
//	std::cin.get();
//
//	return 0;
//}
//
//#include <iostream>
//#include <string>
//#include <vector>
//
//void PrintValue(int value)
//{
//	std::cout << "Value: " << value << std::endl;
//}
//
//void ForEach(const std::vector<int>& values, void(*func)(int))
//{
//	for (int value : values)
//		func(value) ;
//}
//
//int main() 
//{
//	std::vector<int> values = { 1, 5, 4, 2, 3 };
//
//	int a = 5;
//
//	auto lambda = [](int value) { std::cout << "Value: " << value << std::endl; };
//
//	ForEach(values, lambda);
//
//	std::cin.get();
//}
//
//#include <iostream>
//#include <thread>
//#include <chrono>
//
//static bool s_Finished = false;
//
//void DoWork()
//{
//	using namespace std::literals::chrono_literals;
//
//	while (!s_Finished)
//	{
//		std::cout << "working" << std::endl;
//		std::this_thread::sleep_for(1s);
//	}
//}
//
//int main()
//{
//	std::thread worker(DoWork);
//	std::cin.get();
//	s_Finished = true;
//
//	join() 的意思是：“主线程在此默默等待，直到 worker 线程彻底把它的函数执行完，主线程再继续往下走。”
//	worker.join();
//	std::cout << "Finished" << std::endl;
//
//	std::cin.get();
//}
//
//#include <iostream>
//#include <chrono>
//#include <thread>
//
//struct Timer
//{
//	std::chrono::time_point<std::chrono::steady_clock> start, end;
//	std::chrono::duration<float> duration;
//
//	Timer()
//	{
//		start = std::chrono::high_resolution_clock::now();
//	}
//
//	~Timer()
//	{
//		end = std::chrono::high_resolution_clock::now();
//		duration = end - start;
//
//		float ms = duration.count() * 1000.0f;
//		std::cout << "Timer took" << ms << "ms" << std::endl;
//	}
//};
//
//void Function()
//{
//	Timer timer;
//
//	for (int i = 0; i < 100; i++)
//		std::cout << "Hello\n" /*<< std::endl*/;
//}
//
//int main()
//{
//	/*using namespace std::literals::chrono_literals;
//
//	auto start = std::chrono::high_resolution_clock::now(); 
//	std::this_thread::sleep_for(1s);
//	auto end = std::chrono::high_resolution_clock::now();
//
//	std::chrono::duration<float> duration = end - start;
//	std::cout << duration.count() << "s" << std::endl;*/
//
//	Function();
//
//
//	std::cin.get();
//
//}
//
//#include <iostream>
//
//struct Vector2
//{
//	float x, y;
//};
//
//struct Vector4
//{
//	union
//	{
//		struct
//		{
//			float x, y, z, w;
//		};
//		struct
//		{
//			Vector2 a, b;
//		};
//	};
//};
//
//void PrintVector2(const Vector2& vector)
//{
//	std::cout << vector.x << ", " << vector.y << std::endl;
//}
//
//int main()
//{
//	Vector4 vector = { 1.0f, 2.0f, 3.0f, 4.0f };
//	PrintVector2(vector.a);
//	PrintVector2(vector.b);
//	vector.z = 500.f;
//	std::cout << "-------------" << std::endl;
//	PrintVector2(vector.a);
//	PrintVector2(vector.b);
//
//	std::cin.get();
//}
//
//#include <iostream>
//
//class Base
//{
//public:
//	Base() { std::cout << "Base Constructor\n" << std::endl; }
//	virtual 让父类知道可能子类还会有析构函数需要被调用
//	virtual ~Base() { std::cout << "Base Destructor\n" << std::endl; }
//};
//
//class Driver : public Base
//{
//public:
//	Driver() { m_Array = new int[5]; std::cout << "Driver Constructor\n" << std::endl; }
//	~Driver() { delete[] m_Array; std::cout << "Driver Destructor\n" << std::endl; }
//
//private:
//	int* m_Array;
//};
//
//int main()
//{
//	Base* base = new Base();
//	delete base;
//	std::cout << "----------\n" << std::endl;
//	Driver* driver = new Driver();
//	delete driver;
//	std::cout << "----------\n" << std::endl;
//	Base* poly = new Driver();
//	delete poly;
//}
//
//#include <iostream>
//#include <string>
//
//class Entity
//{
//public:
//	virtual void PrintName() {}
//};
//
//class Player : public Entity
//{
//};
//
//class Enemy : public Entity
//{
//};
//
//int main()
//{
//
//	Player* player = new Player();
//	Entity* actuallyEnemy = new Enemy;
//
//	Entity* actuallyPlayer = player;
//
//	人家存储了运行时类型信息(runtime type information)(RTTI)
//	Player* p0 = dynamic_cast<Player*>(actuallyEnemy);
//
//	Player* p1 = dynamic_cast<Player*>(actuallyPlayer);
//}
//
//#include <iostream>
//#include <string>
//#include <tuple>
//
//std::tuple<std::string, int> CreatPersion()
//{
//	return { "wh", 22 };
//}
//
//int main()
//{
//	auto [na, age] = CreatPersion();
//}
//
//#include <iostream>
//#include <fstream>
//#include <optional>
//
//std::optional<std::string> ReadFileAsString(const std::string& filepath)
//{
//	std::ifstream stream(filepath);
//	if (stream)
//	{
//		std::string result;
//		stream.close();
//		return result;
//	}
//
//	return {};
//}
//
//int main()
//{
//	std::optional<std::string> data = ReadFileAsString("data.txt");
//
//	如果数据在optoinal中就返回，如果不在就返回传入的任何值
//	std::string value = data.value_or("Not Present");
//	std::cout << value << std::endl;
//
//	if (data)
//	{
//		std::cout << "File read Successfully!\n";
//	}
//	else
//	{
//		std::cout << "File read UnSuccessfully!\n";
//	}
//
//	std::cin.get();
//}
//
//
//#include <iostream>
//#include <variant>
//
//enum class ErrorCode
//{
//	None = 0, NotFund = 1, NoAccess = 2
//};
//
//std::variant<std::string, ErrorCode> ReadFileAsString()
//{
//	return {};
//}
//
//int main()
//{
//	std::variant<std::string, int> data;
//
//	std::cout << sizeof(data) << "\n";
//
//	data = "Cherno";
//	std::cout << std::get<std::string>(data) << "\n";
//	if (auto value = std::get_if<std::string>(&data))
//	{
//		std::string& v = *value;
//	}
//	else
//	{
//	}
//
//}
//
//#include <iostream>
//#include <variant>
//#include <any>
//
//int main()
//{
//	std::variant<int, std::string> data;
//	data = 2;
//	data = "Cherno";
//	std::string string = std::get<std::string>(data);
//
//	std::cin.get();
//
//}
//
//#include <iostream>
//#include <string>
//
//static uint32_t s_AllocCoutn = 0;
//
//void* operator new(size_t size)
//{
//	s_AllocCoutn++;
//	std::cout << "Allocating" << size << "bytes\n";
//	return malloc(size);
//}
//
//void PrintName(std::string_view name)
//{
//	std::cout << name << std::endl;
//}
//
//int main()
//{
//	const char* name = "Yan Chernikov";
//
//#if 0
//	std::string firstName = name.substr(0, 3);
//	std::string lastName = name.substr(4, 9);
//#else
//	std::string_view firstName(name, 3);
//	std::string_view lastName(name + 4, 9);
//#endif
//
//	PrintName("Cherno");
//	PrintName(firstName);
//	PrintName(lastName);
//
//	std::cout << s_AllocCoutn << " allocations" << std::endl;
//
//	std::cin.get();
//}

//#include <string>
//#include <chrono>
//#include <cmath>
//
//class Timer
//{
//public: 
//	Timer(const char* name)
//		: m_Name(name), m_Stopped(false)
//	{
//		m_StartTimerpoint = std::chrono::high_resolution_clock::now();
//	}
//
//	void Stop()
//	{
//		auto endTimepoint = std::chrono::high_resolution_clock::now();
//
//		long long start = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTimerpoint).time_since_epoch().count();
//		long long end = std::chrono::time_point_cast<std::chrono::milliseconds>(m_StartTimerpoint).time_since_epoch().count();
//	}
//
//};

//#include <iostream>
//
////这个代码从头到尾只用了一个对象，所以叫单例（单个实例）
//class Random
//{
//public:
//	// 1. 禁用拷贝构造函数
//	// 它防止了别人通过复制现有的对象来创建新对象（比如像 Random r2 = r1; 这样是不允许的）。
//	Random(const Random&) = delete;
//
//	static Random& Get()
//	{
//
//		// 创建对象
//		static Random s_Instance;
//		return s_Instance;
//	}
//
//	static float Float() { return Get().IFloat(); }
//
//private:
//	float IFloat() { return m_RandomGenerator; }
//
//	// 2. 私有化默认构造函数
//	Random() {}
//
//	float m_RandomGenerator = 0.5f;
//
//	
//};
//
//
//int main()
//{
//	float number = Random::Float();
// 
//	std::cout << number << std::endl;
//}

//#include <iostream>
//#include <array>
//
//class Array
//{
//	Array(int size)
//	{
//		m_Data = (int*)alloca(size * sizeof(int));
//	}
//private:
//	int* m_Data;
//};

//#include <iostream>
//#include <array>
//
//template<typename T, size_t S>
//class Array
//{
//public:
//	//constexpr：告诉编译器这个函数可以在编译期求值，效率极高。
//	constexpr int Size() const { return S; }
//
//	//用 size_t：因为它是 C++ 官方指定的“大容量、绝对正数”的专属数字类型，专门用来数数和做数组下标。
//	T& operator[](size_t index) { return m_Data[index]; }
//	const T& operator[](size_t index) const { return m_Data[index]; }
//
//	T* Data() { return m_Data; }
//	const T* Data() const { return m_Data; }
//private:
//	T m_Data[S];
//};
//
//int main()
//{
//	int size = 5;
//
//	Array<std::string, 2> data;
//	data[0] = "Cherno";
//	data[1] = "C++";
//	for (size_t i = 0; i < data.Size(); i++)
//	{
//		std::cout << data[i] << std::endl;
//	}
//
//	std::cin.get();
//}  

//#include <iostream>
//#include <vector>
//
//#include <unordered_map>
//
//int main()
//{
//	std::vector<int> values = { 1, 2, 3, 4, 5 };
//
//	using ScoreMap = std::unordered_map<std::string, int>;
//	ScoreMap map;
//	map["Cherno"] = 5;
//	map["C++"] = 2;
//
//	for (ScoreMap::const_iterator it = map.begin();
//		it != map.end(); it++)
//	{
//		auto& key = it->first;
//		auto& value = it->second;
//
//		std::cout << key << "=" << value << std::endl;
//	}
//
//	std::cout << std::endl;
//
//	for (auto kv : map)
//	{
//		auto& key = kv.first;
//		auto& value = kv.second;
//
//		std::cout << key << "=" << value << std::endl;
//	}
//
//	std::cout << std::endl;
//
//	for (auto [key, value] : map)
//	{
//		std::cout << key << "=" << value << std::endl;
//	}
//}

#include <iostream>
#include <sstream>

class HashTable
{
public:
	struct Entry
	{
		std::string Data;
		std::string Status = "never used";
	};
	static const int Size = 26;

public:
	HashTable() = default;

	void Add(const std::string& entryString)
	{
		bool exists = Find(entryString);
		if (exists)
		{
			int insertIndex = GetInsertIndex(entryString);
			m_Entries[insertIndex].Data = entryString;
			m_Entries[insertIndex].Status = "occupied";
		}
	}

	void Delete(const std::string& entryString)
	{
		int index;
		bool exists = Find(entryString, &index);
		if (exists)
			m_Entries[index].Status = "tombstone";
	}

	void Print()
	{
		bool first = true;
		for (int i = 0; i < Size; i++)
		{
			if (m_Entries[i].Status == "occupied")
			{
				if (!first)
					std::cout << ' ';
				std::cout << m_Entries[i].Data;
				first = false;
			}
		}
		std::cout << std::endl;
	}
private:
	int GetIndex(const std::string& entryString)
	{
		return entryString.back() - 'a';
	}

	bool Find(const std::string& entryString, int* outIndex = nullptr)
	{
		int index = GetIndex(entryString);
		while (true)
		{
			if (m_Entries[index].Data == entryString)
			{
				if (outIndex)
					*outIndex = index;
				return true;
			}

			if (m_Entries[index].Status == "never used")
				return false;

			index = (index + 1) % Size;
		}

		return false;
	}

	int GetInsertIndex(const std::string& entryString)
	{
		int index = GetIndex(entryString);
		while (true)
		{
			if (m_Entries[index].Status == "never used" || m_Entries[index].Status == "tombstone")
				return index;

			index == (index + 1) % Size;
		}

		return -1;
	}
private:
	Entry m_Entries[Size];

};

int main()
{
	std::string input;
	getline(std::cin, input);

	HashTable hashTable;

	std::stringstream ss(input);
	while (ss.good())
	{
		std::string token;
		ss >> token;

		std::string entryString = token.substr(1);
		if (token[0] == 'A')
		{
			hashTable.Add(entryString);
		}
		else if(token[0] == 'D')
		{
			hashTable.Delete(entryString);
		}
	}

	hashTable.Print();
}