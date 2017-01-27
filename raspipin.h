/**
* @descr Header of the RaspiPin class
* 
* @author K.Bergue
* @version 1.0.1
* @change 27.01.2017 by Author
*/

#ifndef RASPIPIN_H
#define RASPIPIN_H

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_MAX 3 //taille maximum du buffer
#define DIRECTION_MAX 35 //taille maximale du string contenant le chemin vers direction
#define VALUE_MAX 30 //taille maximale du string contenant le chemin vers value

/**
 * @descr Ce namespace est utile afin de rendre l'objet compatible
 * avec tous les programmes où il est susceptible d'être implementé:
 * dans le cas d'un simple define, si on declare un #define IN false
 * l'utilisateur ne pourra plus definir de IN sous peine de voir cet objet
 * ne plus fonctionner, dans ce cas il doit faire "Raspi::IO::IN" certes plus long
 * mais evitant tous les problèmes mentionnés ci-dessus. 
 * L'autre problème que cette synthaxe résoud est lors de la construction de 
 * l'objet: en demandant obligatoirement une variable de type Raspi::GPIO on
 * évite que l'utilisateur rentre "50000" dans le constructeur et puisse
 * potentiellement planter le programme
 */
 
namespace Raspi
{
    enum class IO : bool
    {
        IN = false,
        OUT = true
    };

    enum class VALUE : bool
    {
        HIGH = true,
        LOW = false
    };

    enum class PIN : unsigned int //pins physique du raspberry
    {
        PIN_3 = 2,
        PIN_5 = 3,
        PIN_7 = 4,
        PIN_8 = 14,
        PIN_10 = 15,
        PIN_11 = 17,
        PIN_12 = 18,
        PIN_13 = 27,
        PIN_15 = 22,
        PIN_16 = 23,
        PIN_18 = 24,
        PIN_19 = 10,
        PIN_21 = 9,
        PIN_22 = 25,
        PIN_23 = 11,
        PIN_24 = 8,
        PIN_26 = 7,
        PIN_27 = 0,
        PIN_28 = 1,
        PIN_29 = 5,
        PIN_31 = 6,
        PIN_32 = 12,
        PIN_33 = 13,
        PIN_35 = 19,
        PIN_36 = 16,
        PIN_37 = 26,
        PIN_38 = 20,
        PIN_40 = 21
    };

    enum class GPIO : unsigned int //GPIO "normaux" donnés par la documentation
    {
        GPIO_2 = 2,
        GPIO_3 = 3,
        GPIO_4 = 4,
        GPIO_14 = 14,
        GPIO_15 = 15,
        GPIO_17 = 17,
        GPIO_18 = 18,
        GPIO_27 = 27,
        GPIO_22 = 22,
        GPIO_23 = 23,
        GPIO_24 = 24,
        GPIO_10 = 10,
        GPIO_9 = 9,
        GPIO_25 = 25,
        GPIO_11 = 11,
        GPIO_8 = 8,
        GPIO_7 = 7,
        GPIO_0 = 0,
        GPIO_1 = 1,
        GPIO_5 = 5,
        GPIO_6 = 6,
        GPIO_12 = 12,
        GPIO_13 = 13,
        GPIO_19 = 19,
        GPIO_16 = 16,
        GPIO_26 = 26,
        GPIO_20 = 20,
        GPIO_21 = 21,

        SDA1 = Raspi::GPIO::GPIO_2,
        SCL1 = Raspi::GPIO::GPIO_3,
        GPIO_GCLK = Raspi::GPIO::GPIO_4,
        TXD0 = Raspi::GPIO::GPIO_14,
        RXD0 = Raspi::GPIO::GPIO_15,
        GPIO_GEN0 = Raspi::GPIO::GPIO_17,
        GPIO_GEN1 = Raspi::GPIO::GPIO_18,
        GPIO_GEN2 = Raspi::GPIO::GPIO_27,
        GPIO_GEN3 = Raspi::GPIO::GPIO_22,
        GPIO_GEN4 = Raspi::GPIO::GPIO_23,
        GPIO_GEN5 = Raspi::GPIO::GPIO_24,
        SPI_MOSI = Raspi::GPIO::GPIO_10,
        SPI_MISO = Raspi::GPIO::GPIO_9,
        GPIO_GEN6 = Raspi::GPIO::GPIO_25,
        SPI_CLK = Raspi::GPIO::GPIO_11,
        SPI_CE0_N = Raspi::GPIO::GPIO_8,
        SPI_CE1_N = Raspi::GPIO::GPIO_7,
        ID_SD = 0,
        ID_SC = 1
    };

    enum class GPIO_GEN : unsigned int //GPIO utilisé par la commande "gpio readall"
    {
        SDA_1 = 2,
        SCL_1 = 3,
        GPIO_7 = 4,
        TxD = 14,
        RxD = 15,
        GPIO_0 = 17,
        GPIO_1 = 18,
        GPIO_2 = 27,
        GPIO_3 = 22,
        GPIO_4 = 23,
        GPIO_5 = 24,
        MOSI = 10,
        MISO = 9,
        GPIO_6 = 25,
        SCLK = 11,
        CE0 = 8,
        CE1 = 7,
        SDA_0 = 0,
        SCL_0 = 1,
        GPIO_21 = 5,
        GPIO_22 = 6,
        GPIO_26 = 12,
        GPIO_23 = 13,
        GPIO_24 = 19,
        GPIO_27 = 16,
        GPIO_25 = 26,
        GPIO_28 = 20,
        GPIO_29 = 21
    };


}
/**
 * @invariant
 * @descr Chaque instance de cette classe représente un pin physique de la raspberry
 */
 
class RaspiPin
{
private:
    const unsigned int pin;
    Raspi::IO dir;
    void exportPin(void);
    void unexportPin(void);

public:
    RaspiPin(Raspi::GPIO userPin, Raspi::IO userDir = Raspi::IO::IN);
    void setDirection(Raspi::IO direction);
    Raspi::IO getDirection() {return dir;}
    bool getValue(void);
    void setValue(bool value);
    virtual ~RaspiPin(void);

};

#endif // RASPIPIN_H
