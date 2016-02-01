#include "Socket.h"


// class HostAddress

/**
* Конструктор по умолчанию
*/
HostAddress::HostAddress()
	:
		_address(0) //адрес хоста в сетевом порядке байт
{
}

/**
* Конструктор
* @param address - строка с адресом
*/
HostAddress::HostAddress
	(
		const string& address
	)
{
	//устанавливаем требуемый адрес
	SetAddress(address);
}

/**
* Конструктор
* @param address - число с адресом (не в сетевом порядке байт)
*/
HostAddress::HostAddress
	(
		const Address& address
	)
{
	//устанавливаем требуемый адрес
	SetAddress(address);
}

/**
* Получение адреса хоста в сетевом порядке байт
* @return адрес хоста в сетевом порядке байт
*/
Address HostAddress::GetAddress() const
{
	//возвращаем адрес
	return _address;
}

/**
* Установка нового адреса хоста
* @param address - строка с адресом
* @return признак успешной (true) или неуспешной (false) установки
*/
bool HostAddress::SetAddress
	(
		const string& address
	)
{
	Address addr; //промежуточная переменная для хранения адреса

	//получаем адрес из строки
	addr = inet_addr(address.c_str());
	if (addr == INADDR_NONE) //если конвертация прошла с ошибкой
	{
		//ошибка при установке нового адреса
		return false;
	}
	_address = addr; //устанавливаем новое значение адреса

	//установка нового адреса была успешной
	return true;
}

/**
* Установка нового адреса хоста
* @param address - число с адресом (не в сетевом порядке байт)
*/
void HostAddress::SetAddress
	(
		const Address& address
	)
{
	//устанавливаем новый адрес с предварительным переводом в сетевой порядок байт
	_address = htonl(address);
}


// class SocketAddress

/**
* Конструктор
* @param port - номер порта
* @param hostAddress - адрес хоста
*/
SocketAddress::SocketAddress
	(
		Port port,
		const HostAddress& hostAddress
	)
{
	_socketAddress.sin_family = AF_INET;
	_socketAddress.sin_port = htons(port);
	_socketAddress.sin_addr.s_addr = hostAddress.GetAddress();
}

/**
* Конструктор
* @param port - номер порта
* @param address - число с адресос хоста (не в сетевом порядке байт)
*/
SocketAddress::SocketAddress
	(
		Port port,
		const Address& address
	)
{
	_socketAddress.sin_family = AF_INET;
	_socketAddress.sin_port = htons(port);
	_socketAddress.sin_addr.s_addr = htonl(address);
}

/**
* Получить указатель на структуру sockaddr
* @return указатель на структуру sockaddr
*/
const sockaddr* SocketAddress::GetSockaddr() const
{
	return (sockaddr*)&_socketAddress;
}


#ifndef NIX

// class SocketInitializer

// данные о версии сокетов и пр.
//static
WSADATA SocketInitializer::_socketData;

/**
* Конструктор
* @param minorVersion - наинизшая требуемая версия сокетов
* @param majorVersion - наивысшая требуемая версия сокетов
*/
SocketInitializer::SocketInitializer
	(
		Byte minorVersion,
		Byte majorVersion
	)
{
	//начинаем работу с сокетами
	Start(minorVersion, majorVersion);
}

/**
* Деструктор
*/
SocketInitializer::~SocketInitializer()
{
	//завершаем работу с сокетами
	Clean();
}

/**
* Получить структуру с информацией о сокетах
* @return структура с информацией о сокетах
*/
const WSADATA& SocketInitializer::GetSocketData() const
{
	//возвращаем данные о текущей версии сокетов и пр.
	return _socketData;
}

/**
* Начать работу с сокетами
* @param minorVersion - наинизшая требуемая версия сокетов
* @param majorVersion - наивысшая требуемая версия сокетов
* @return признак успешного начала
*/
//static
bool SocketInitializer::Start
	(
		Byte minorVersion,
		Byte majorVersion
	)
{
	WORD versionRequested; //требуемый диапазон версий сокетов

	//формируем требуемый диапазон версий сокетов виде одного числа
	versionRequested = MAKEWORD(minorVersion, majorVersion);
	//начинаем работу с сокетами
	if (WSAStartup(versionRequested, &_socketData) != 0)
	{
		//требуемые версии сокетов не найдены
		return false;
	}

	//требуемая версия сокетов найдена, ошибок нет
	return true;
}

/**
* Завершить работу с сокетами
* @return признак успешного завершения
*/
//static
bool SocketInitializer::Clean()
{
	//завершаем работу с сокетами
	if (WSACleanup() != 0)
	{
		//работа с сокетами не была корректно завершена
		return false;
	}

	//работа с сокетами корректно завершена, ошибок нет
	return true;
}

#endif