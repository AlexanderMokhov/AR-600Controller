// модуль для определения интерфейсов вспомогательных классов,
// необходимых для работы с сокетами

#ifndef SOCKET_H

#define SOCKET_H

#ifndef NIX

#include <Winsock2.h>

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#endif

#include <string>


using std::string;


// один байт
typedef char Byte;

// адрес хоста
typedef unsigned long Address;

// номер порта
typedef unsigned short Port;


/**
* Класс адреса хоста
*/
class HostAddress
{
public:

	// Конструкторы

	/**
	* Конструктор по умолчанию
	*/
	HostAddress();

	/**
	* Конструктор
	* @param address - строка с адресом
	*/
	HostAddress
		(
			const string& address
		);

	/**
	* Конструктор
	* @param address - число с адресом (не в сетевом порядке байт)
	*/
	HostAddress
		(
			const Address& address
		);

	
	// Селекторы

	/**
	* Получение адреса хоста в сетевом порядке байт
	* @return адрес хоста в сетевом порядке байт
	*/
	Address GetAddress() const;

	
	// Модификаторы
	
	/**
	* Установка нового адреса хоста
	* @param address - строка с адресом
	* @return признак успешной (true) или неуспешной (false) установки
	*/
	bool SetAddress
		(
			const string& address
		);

	/**
	* Установка нового адреса хоста
	* @param address - число с адресом (не в сетевом порядке байт)
	*/
	void SetAddress
		(
			const Address& address
		);


protected:

	// адрес хоста в сетевом порядке байт
	Address _address;

};


/**
* Класс адреса сокета
*/
class SocketAddress
{
public:

	// Конструкторы

	/**
	* Конструктор
	* @param port - номер порта
	* @param hostAddress - адрес хоста
	*/
	SocketAddress
		(
			Port port = 50000,
			const HostAddress& hostAddress = HostAddress("127.0.0.1")
		);

	/**
	* Конструктор
	* @param port - номер порта
	* @param address - число с адресос хоста (не в сетевом порядке байт)
	*/
	SocketAddress
		(
			Port port,
			const Address& address
		);


	// Селекторы

	/**
	* Получить указатель на структуру sockaddr
	* @return указатель на структуру sockaddr
	*/
	const sockaddr* GetSockaddr() const;


protected:

	// структура, хранящая информацию о типе протокола, номере порта и IP-адресе
	sockaddr_in _socketAddress;

};


#ifndef NIX

/**
* Класс инициализации/деинициализации работы с сокетами
*/
class SocketInitializer
{
public:

	// Конструкторы и деструктор

	/**
	* Конструктор
	* @param minorVersion - наинизшая требуемая версия сокетов
	* @param majorVersion - наивысшая требуемая версия сокетов
	*/
	SocketInitializer
		(
			Byte minorVersion = 2,
			Byte majorVersion = 2
		);

	/**
	* Деструктор
	*/
	~SocketInitializer();


	// Селекторы

	/**
	* Получить структуру с информацией о сокетах
	* @return структура с информацией о сокетах
	*/
	const WSADATA& GetSocketData() const;


	// Инициализация и деинициализация работы с сокетами

	/**
	* Начать работу с сокетами
	* @param minorVersion - наинизшая требуемая версия сокетов
	* @param majorVersion - наивысшая требуемая версия сокетов
	* @return признак успешного начала
	*/
	static
	bool Start
		(
			Byte minorVersion = 2,
			Byte majorVersion = 2
		);

	/**
	* Завершить работу с сокетами
	* @return признак успешного завершения
	*/
	static
	bool Clean();


protected:
	
	// структура с данными о версии сокетов и пр.
	static
	WSADATA _socketData;

};

#endif

#endif // SOCKET_H
