/**
* @descr Declaration of the RaspiPin class
* 
* @author K.Bergue
* @version 1.0.1
* @change 27.01.2017 by Author
*/

#include "raspipin.h"

/**
 * @descr Un contructeur de RaspiPin
 * 
 * @param userPin
 * GPIO from the Raspi::GPIO enum
 * 
 * @param userDir
 * Can take the value Raspi::IO::IN or Raspi::IO::OUT
 * 
 * @return nothing
 */
RaspiPin::RaspiPin(Raspi::GPIO userPin, Raspi::IO userDir) : pin(userPin)
{
    dir = userDir;
    exportPin();
    setDirection(dir);
}

/**
 * @descr Permet d'indiquer à sysfs que l'on souhaite controller un pin
 * 
 * @return nothing
 */
void RaspiPin::exportPin()
{
    char buffer[BUFFER_MAX];
    ssize_t bytes_written;
    int fd;

    do
    {
        fd = open("/sys/class/gpio/export", O_WRONLY);
    } while(fd == -1);

    bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
    write(fd, buffer, bytes_written);
    close(fd);
}

/**
 * @descr Opération inverse d'exportPin
 * 
 * @return nothing
 */
void RaspiPin::unexportPin()
{
    char buffer[BUFFER_MAX];
    ssize_t bytes_written;
    int fd;

    do
    {
        fd = open("/sys/class/gpio/unexport", O_WRONLY);
    } while(fd == -1);

    bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
    write(fd, buffer, bytes_written);
    close(fd);
}

/**
 * @descr Permet de modifier la direction du pin
 * 
 * @param direction
 * Peut avoir la valeur Raspi::IO::IN ou Raspi::IO::OUT
 * 
 * @return nothing
 */
void RaspiPin::setDirection(Raspi::IO direction)
{
    static const char s_directions_str[]  = "in\0out";
    char path[DIRECTION_MAX];
    int fd;

    snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);

    do
    {
        fd = open(path, O_WRONLY);
    } while(fd == -1);

    do
    {

    } while(-1 == write(fd, &s_directions_str[Raspi::IO::IN == direction ? 0 : 3], Raspi::IO::IN == direction ? 2 : 3));

    close(fd);
    dir = direction;
}

/**
 * @descr Permet de récupérer la valeur sur le pin
 * 
 * @return Raspi::VALUE::HIGH ou Raspi::VALUE::LOW
 */
bool RaspiPin::getValue()
{
    char path[VALUE_MAX];
    char value_str[3];
    int fd;

    snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
    do
    {
        fd = open(path, O_RDONLY);
    } while(fd == -1);

    do
    {

    } while(-1 == read(fd, value_str, 3));

    close(fd);

    return(atoi(value_str));
}

/**
 * @descr Permet de modiier la valeur du pin si celui-ci est réglé en sortie
 * 
 * @return nothing
 */
void RaspiPin::setValue(bool value)
{
	if(dir == Raspi::IO::OUT)
	{
		static const char s_values_str[] = "01";

		char path[VALUE_MAX];
		int fd;

		snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
		do
		{
			fd = open(path, O_WRONLY);
		} while(fd == -1);

		do
		{

		}
		while (1 != write(fd, &s_values_str[0 == value ? 0 : 1], 1));

		close(fd);
	}
    else
		//error
}

/**
 * @descr destructeur de l'objet
 */
RaspiPin::~RaspiPin()
{
    unexportPin();
}

