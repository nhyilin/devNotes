from skyfield.api import Topos, load
from skyfield.sgp4lib import EarthSatellite
import datetime
from skyfield.api import EarthSatellite, load, wgs84
from skyfield.elementslib import osculating_elements_of
from skyfield.timelib import Time
from skyfield.api import load
import numpy as np


def Cal():
    # 加载星历数据
    ts = load.timescale()
    planets = load('de421.bsp')

    # 假设的六根数和时间
    # 替换为您的卫星数据：周期, 偏心率, 倾角, 升交点赤经, 近地点幅角, 平近点角
    elements = '1 99999U          24110.00000000  .00023208  00000-0  11486-2 0 00003'
    line2 = '2 99999 085.6190 068.1231 0007538 110.9468 344.1951 15.17851882000013'

    # 创建卫星对象
    satellite = EarthSatellite(elements, line2, 'ISS (ZARYA)', ts)

    # 计算位置
    t = ts.utc(2024, 4, 20, 0, 0, 0)
    geocentric = satellite.at(t)

    # 获取卫星的地心坐标（J2000）
    position = geocentric.position.km
    velocity = geocentric.velocity.km_per_s
    print('Position (J2000):', position)
    print('Velocity (J2000):', velocity)

    # 预测未来一天的位置
    dt = datetime.timedelta(days=1)
    future_time = ts.utc(t.utc_datetime() + dt)
    future_geocentric = satellite.at(future_time)
    future_position = future_geocentric.position.km
    future_velocity = future_geocentric.velocity.km_per_s
    print('Future Position (J2000):', future_position)
    print('Future Velocity (J2000):', future_velocity)


def main():
    Cal()


if __name__ == '__main__':
    main()
