import nmap # For network scanning
import bluetooth # For BT scanning
from scapy.all import *

def scan_environment():
    print("--- SCANNING SOVEREIGN PERIMETER ---")
    
    # 1. Look for "Square" WiFi Devices
    # This finds everything currently active on your local IP range
    nm = nmap.PortScanner()
    nm.scan(hosts='192.168.1.0/24', arguments='-sn')
    for host in nm.all_hosts():
        print(f"[WiFi Device] Found: {host} ({nm[host].hostname()})")

    # 2. Look for Bluetooth "Grit"
    # This finds hidden trackers, earpieces, or 'Saurian' phones
    print("Scanning Bluetooth Spectrum...")
    nearby_devices = bluetooth.discover_devices(lookup_names=True)
    for addr, name in nearby_devices:
        print(f"[BT Device] Found: {name} - Address: {addr}")

# This logic checks if the 'Total Signal Count' changes suddenly
