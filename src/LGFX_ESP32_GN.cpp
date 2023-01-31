#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <LGFX_ESP32_GN.h>

#define LCD_BL 5
#define LCD_SDA 19
#define LCD_SCK 18
#define LCD_CS 21
#define LCD_DC 23
#define LCD_RES 22

LGFX::LGFX()
{
  {
    auto cfg = _bus_instance.config();

    cfg.spi_host = VSPI_HOST;
    cfg.spi_mode = 3;
    cfg.freq_write = 27000000;
    cfg.freq_read = 20000000;
    cfg.spi_3wire = true;
    cfg.use_lock = true;
    cfg.dma_channel = 0;
    cfg.pin_sclk = LCD_SCK;
    cfg.pin_mosi = LCD_SDA;
    cfg.pin_miso = -1;
    cfg.pin_dc = LCD_DC;
    _bus_instance.config(cfg);
    _panel_instance.setBus(&_bus_instance);
  }

  {
    auto cfg = _panel_instance.config();
    cfg.pin_cs = LCD_CS;
    cfg.pin_rst = LCD_RES;
    cfg.pin_busy = -1;
    cfg.panel_width = 135;
    cfg.panel_height = 240;
    cfg.offset_x = 52;
    cfg.offset_y = 40;
    cfg.offset_rotation = 0;
    cfg.dummy_read_pixel = 8;
    cfg.dummy_read_bits = 1;
    cfg.readable = true;
    cfg.invert = true;
    cfg.rgb_order = false;
    cfg.dlen_16bit = false;
    cfg.bus_shared = true;
    _panel_instance.config(cfg);
  }

  {
    auto cfg = _light_instance.config();

    cfg.pin_bl = LCD_BL;
    cfg.invert = true;
    cfg.freq = 44100;
    cfg.pwm_channel = 7;

    _light_instance.config(cfg);
    _panel_instance.setLight(&_light_instance);
  }

  setPanel(&_panel_instance);
}
