#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h> // Include for ntohs() and ntohl()

// Define the structure of a protocol unit
typedef struct {
    uint8_t magic;
    uint8_t len_unit;
    uint8_t type;
    uint8_t block;
    uint32_t uid;
    uint32_t nonce32nt;
    uint32_t nonce32nr;
    uint32_t nonce32ar;
    uint8_t *padding;
} protocol_unit_t;

// Define the structure of a packet
typedef struct {
    uint16_t length;
    protocol_unit_t *units;
} packet_t;

// Function to create a new packet
packet_t create_packet(protocol_unit_t *units, uint16_t num_units) {
    packet_t packet;
    packet.length = 2; // 2 bytes for the packet length

    for (uint16_t i = 0; i < num_units; i++) {
        packet.length += units[i].len_unit + 2;
    }

    packet.units = units;
    return packet;
}

// Function to process a packet
void process_packet(packet_t packet) {
    uint16_t offset = 0;
    uint8_t *unit_data = (uint8_t *)packet.units;

    while (offset < packet.length - 2) {
        protocol_unit_t *unit = (protocol_unit_t *)(unit_data + offset);

        printf("Processing unit at offset %d:\n", offset);
        printf("magic: 0x%02X\n", unit->magic);
        printf("len_unit: %u\n", unit->len_unit);
        printf("type: %u\n", unit->type);
        printf("block: %u\n", unit->block);
        printf("uid: 0x%08X\n", ntohl(unit->uid));
        printf("nonce32 nt nr ar\n");
        printf("0x%08X 0x%08X 0x%08X\n", ntohl(unit->nonce32nt), ntohl(unit->nonce32nr), ntohl(unit->nonce32ar));

        offset += unit->len_unit + 2;
    }
}


// Function to read a packet from standard input
packet_t read_packet_stdio() {
    packet_t packet;
    fread(&packet.length, sizeof(uint16_t), 1, stdin);
    printf("length: %u\n", packet.length);

    // Allocate memory for the units in the packet
    uint8_t *raw_units = (uint8_t *)malloc(packet.length - 2);
    if (raw_units == NULL) {
        fprintf(stderr, "Failed to allocate memory for units.\n");
        exit(1);
    }

    // Read the units from standard input
    fread(raw_units, sizeof(uint8_t), packet.length - 2, stdin);

    packet.units = (protocol_unit_t *)raw_units;
    return packet;
}

// Function to read a packet from a file
packet_t read_packet_file(FILE *file) {
    packet_t packet;
    fread(&packet.length, sizeof(uint16_t), 1, file);

    // Allocate memory for the units in the packet
    uint8_t *raw_units = (uint8_t *)malloc(packet.length - 2);
    if (raw_units == NULL) {
        fprintf(stderr, "Failed to allocate memory for units.\n");
        exit(1);
    }

    // Read the units from the file
    fread(raw_units, sizeof(uint8_t), packet.length - 2, file);

    packet.units = (protocol_unit_t *)raw_units;
    return packet;
}

int main() {
//    const char *filename = "detec";

//    // Open the file containing the packet
//    FILE *file = fopen(filename, "rb");
//    if (file == NULL) {
//        fprintf(stderr, "Failed to open the file '%s'.\n", filename);
//        exit(1);
//    }

//    // Read a packet from the file
//    packet_t packet = read_packet_file(file);

//    // Close the file
//    fclose(file);

    // Read a packet from standard input
    packet_t packet = read_packet_stdio();

    // Process the packet
    process_packet(packet);

    // Free the allocated memory
    free(packet.units);

    return 0;
}
