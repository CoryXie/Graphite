#pragma once

#include <cmath>
#include "fixed_types.h"
#include "log.h"

class Latency
{
   public:
      Latency(UInt64 cycles = 0, float frequency = 0):_cycles(cycles), _frequency(frequency){};
      Latency(const Latency& lat):_cycles(lat._cycles),
                                  _frequency(lat._frequency) {};
      ~Latency(){};

      Latency operator+(const Latency& lat) const;

      Latency operator=(const Latency& lat)
            { return Latency(lat._cycles, lat._frequency);}

      Latency operator+=(const Latency& lat);

      UInt64 toPicosec() const;

      UInt64 getCycles() const {return _cycles; }

   private:
      UInt64 _cycles;
      float _frequency;
};

class Time
{
   public:
      explicit Time(UInt64 picosec=0):_picosec(picosec){}
      Time(const Time& time):_picosec(time._picosec){}
      Time(const Latency& lat): _picosec(lat.toPicosec()){}
      ~Time(){};

      Time operator+(const Latency& lat) const
            { return Time (_picosec + lat.toPicosec()); }

      Time operator+(const Time& time) const
            { return Time(_picosec + time._picosec); }

      Time operator-(const Time& time) const
            { return Time(_picosec - time._picosec); }

      bool operator>(const Time& time)
            { return _picosec > time._picosec; }

      bool operator<(const Time& time) const
            { return _picosec < time._picosec; }

      bool operator<=(const Time& time)
            { return _picosec <= time._picosec; }

      bool operator>=(const Time& time)
            { return _picosec >= time._picosec; }

      bool operator==(const UInt64& picosec)
            { return _picosec == picosec; } 

      void operator+=(const Time& time)
            { _picosec += time._picosec; }

      void operator-=(const Time& time)
            { _picosec -= time._picosec; }

      Time operator=(const Time& time)
            { _picosec = time._picosec; return *this; }

      UInt64 getTime() const { return _picosec; }

      UInt64 toCycles(float frequency) const;

      UInt64 toPicosec() const { return _picosec; }

      UInt64 toNanosec() const;

   private:
      UInt64 _picosec;
};


inline UInt64 Latency::toPicosec() const
{
   UInt64 picosec = (UInt64) ceil( ((double) 1000*_cycles) /  ((double) _frequency) );

   return picosec;
}

inline Latency Latency::operator+(const Latency& lat) const
{
   LOG_ASSERT_ERROR(_frequency == lat._frequency,
      "Attempting to add latencies from different frequencies");

   return Latency(_cycles + lat._cycles, _frequency);
}

inline Latency Latency::operator+=(const Latency& lat)
{
   LOG_ASSERT_ERROR(_frequency == lat._frequency,
      "Attempting to add latencies from different frequencies");
   _cycles += lat._cycles;
   return *this;
}

inline UInt64 Time::toCycles(float frequency) const
{
   UInt64 cycles = (UInt64) ceil(((double) (_picosec) * ((double) frequency))/double(1000));

   return cycles;
}

inline UInt64 Time::toNanosec() const
{
   return (UInt64) ceil(((double) _picosec)/double(1000));
}
