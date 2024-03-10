import asyncio
from bleak import BleakClient
import struct

arduino_address = "941A71E3-8B13-357D-7037-447C9C5F6037"
imu_data_uuid = "12345678-1234-1234-1234-123456789013"
led_control_uuid = "12345678-1234-1234-1234-123456789014"

async def run():
    async with BleakClient(arduino_address) as client:
        print("Connected!")

        while True:
            # Read IMU data
            imu_data = await client.read_gatt_char(imu_data_uuid)
            converted_data = struct.unpack('<f', bytearray(imu_data))
            print("IMU Data:", converted_data)

            # Control LED
            led_control = input("How many times to blink light: ").strip()
            if led_control in ["0", "1", "2", "3", "4"]:
                await client.write_gatt_char(led_control_uuid, bytearray([int(led_control)]), response=True)
            else:
                print("Invalid input. Please type a number between 0 and 5, inclusive.")

loop = asyncio.get_event_loop()
loop.run_until_complete(run())
