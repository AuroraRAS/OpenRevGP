# OpenRevGP

OpenRevGP is a third-party, open-source host computer program designed for use with the ChameleonMini RevGP. It provides support for basic functions such as uploading dumps, downloading dumps, and downloading detection data.

ChameleonMini RevGP, also known as "PCR Panda V2.0" or "pcr532", is a low-cost Chinese clone of the ChameleonMini.

The official host computer program for ChameleonMini RevGP can be found at [https://www.rfidfans.com/thread/9](https://www.rfidfans.com/thread/9) (Chinese only). However, this official software is bulky, obscure, and proprietary. It also carries the risk of failure due to offline servers and is not compatible with Linux environments.

## Features

- Upload dump files
- Download dump files
- Download detection data

## Compatibility

OpenRevGP is designed to work with:

- ChameleonMini RevGP
- PCR Panda V2.0
- pcr532

## Requirements

- Compatible ChameleonMini RevGP device
- Linux environment
- stty - change and print terminal line settings
- chat - Automated conversational script with a modem
- rx - XMODEM, YMODEM, ZMODEM (Batch) file receive
- (optional) rfcomm - RFCOMM configuration utility
- (optional) mfkey32v2 - MIFARE Classic key recovery - based 32 bits of keystream  VERSION2

## Build

`make`

## Options

Select a slot

- `-s <slot_number>` | `--slot <slot_number>`

Select slot group, 1 or 2

- `-sg <slot_group_number>` | `--slot-group <slot_group_number>`

Save detection data to a file

- `-dg <detection_filename>` | `--detection-get <detection_filename>`

Clean detection data for selected slot

- `-dc` | `--detection-clean`

Clean detection data for all slots

- `-dca` | `--detection-clean-all`

Get card dump data from selected slot

- `-g <dump_filename>` | `--get <dump_filename>`

Put card dump data to selected slot

- `-p <dump_filename>` | `--put <dump_filename>`

## Usage

`./revpg.sh <-d BluetoothDevAddress> [-s Slot] [-sg SlotGroup] [-dg DetectionDataFile] [-dc] [-dca] [-g DumpFile]`

Example:

`./revpg.sh -d AA:BB:CC:DD:EE:FF -sg 1 -s 2 -dg detec.bin`

Recovery keys

`./DetectionData < detec.bin`

`mfkey32v2 <uid> <nt> <nr> <ar> <nt2> <nr2> <ar2>`

## License

OpenRevGP is licensed under the GNU General Public License v3.0 (GPLv3). For more information, please see the [LICENSE](LICENSE) file.