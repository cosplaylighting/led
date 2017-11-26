#ifndef __LED_ARRAY_H__
#define __LED_ARRAY_H__



#include "led.h"




class led_array : public led {
	public:



	////////////////////////////////////////////////////////////////////////////
	// CONSTRUCTOR - PASS IN THE PIN FOR THE LEDS, AS WELL AS THE LED COUNT
	////////////////////////////////////////////////////////////////////////////
	INLINE led_array(uint8_t led_pin, uint16_t led_total) : led(led_pin, led_total) {
		_array = (color_t*) malloc(sizeof(color_t) * led_total);
	}




	////////////////////////////////////////////////////////////////////////////
	// DESTRUCTOR - TURN OFF ALL LEDS AND FREE ALL OF THE LED BUFFER MEMORY
	////////////////////////////////////////////////////////////////////////////
	virtual ~led_array() {
		clear();
		show();
		free(_array);
	}




	////////////////////////////////////////////////////////////////////////////
	//READ A SINGLE PIXEL FROM THE LED STRIP
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t read(int16_t index) const {
		return (index >= 0  &&  index < total())
				? _array[index]
				: color_t::black();
	}

	INLINE color_t read_unsafe(int16_t index) const {
		return _array[index];
	}




	////////////////////////////////////////////////////////////////////////////
	//WRITE A SINGLE PIXEL VALUE INTO THE LED STRIP
	////////////////////////////////////////////////////////////////////////////
	INLINE void write(int16_t index, color_t color) {
		if (index >=0  &&  index < total()) _array[index] = color;
	}

	INLINE void write(int16_t index, uint8_t r, uint8_t g, uint8_t b) {
		write(index, color_t(r, g, b));
	}

	INLINE void write_unsafe(int16_t index, color_t color) {
		_array[index] = color;
	}

	INLINE void write_unsafe(int16_t index, uint8_t r, uint8_t g, uint8_t b) {
		write_unsafe(index, color_t(r, g, b));
	}




	////////////////////////////////////////////////////////////////////////////
	//WRITE A PIXEL VALUE TO THE GRID, AND RETURN THE PREVIOUSLY WRITTEN VALUE
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t swap(int16_t index, color_t color) {
		color_t ret = read(index);
		write(index, color);
		return ret;
	}

	INLINE color_t swap_unsafe(int16_t index, color_t color) {
		color_t ret = read_unsafe(index);
		write_unsafe(index, color);
		return ret;
	}




	////////////////////////////////////////////////////////////////////////////
	//RENDER LED ARRAY OUT TO GRID
	////////////////////////////////////////////////////////////////////////////
	void show() {
		begin();
		for (int16_t i=0; i<total(); i++) {
			pixel(read_unsafe(i));
		}
		end();
	}




	////////////////////////////////////////////////////////////////////////////
	//FILL THE ENTIRE STRIP WITH A SINGLE COLOR
	////////////////////////////////////////////////////////////////////////////
	INLINE void clear() { fill(color_t::black()); }

	void fill(color_t color) {
		for (int16_t i=0; i<total(); i++) write_unsafe(i, color);
	}




	////////////////////////////////////////////////////////////////////////////
	//GET A POINTER TO THE RAW BINARY PIXEL DATA
	////////////////////////////////////////////////////////////////////////////
	INLINE color_t *pixels() const {
		return _array;
	}




	private:
		color_t *_array;
};




#endif //__LED_ARRAY_H__