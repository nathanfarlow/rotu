import os
import time
import random
import argparse

# Path to the Dolphin Emulator configuration and pipe directories
config_path = os.path.expanduser("~/.config/dolphin-emu/Profiles/GCPad/auto.ini")
pipe_dir = os.path.expanduser("~/.local/share/dolphin-emu/Pipes")
pipe_path = os.path.join(pipe_dir, "pipe1")

# Configuration string to write
config_str = """[Profile]
Device = Pipe/0/pipe1
Buttons/A = `Button A`
Buttons/B = `Button B`
Buttons/X = `Button X`
Buttons/Y = `Button Y`
Buttons/Z = `Button Z`
Buttons/Start = `Button START`
D-Pad/Up = `Button D_UP`
D-Pad/Down = `Button D_DOWN`
D-Pad/Left = `Button D_LEFT`
D-Pad/Right = `Button D_RIGHT`
Triggers/L = `Button L`
Triggers/R = `Button R`
Main Stick/Up = `Axis MAIN Y -`
Main Stick/Down =  `Axis MAIN Y +`
Main Stick/Left = `Axis MAIN X -`
Main Stick/Right = `Axis MAIN X +`
C-Stick/Up = `Axis C Y -`
C-Stick/Down =  `Axis C Y +`
C-Stick/Left = `Axis C X -`
C-Stick/Right = `Axis C X +`
"""


# Function to write the configuration
def write_config(path, content):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    with open(path, "w") as file:
        file.write(content)


# Function to create and open a pipe if it doesn't exist
def ensure_pipe(path):
    os.makedirs(os.path.dirname(path), exist_ok=True)
    if not os.path.exists(path):
        os.mkfifo(path)


# Function to send commands to the pipe
def send_command(command, pipe):
    with open(pipe, "w") as p:
        p.write(command + "\n")


def press_button(button, delay=0.1):
    send_command(f"PRESS {button}", pipe_path)
    time.sleep(delay)
    send_command(f"RELEASE {button}", pipe_path)


def fuzz(can_pause: bool = False):
    # List of buttons to fuzz
    buttons = [
        "A",
        "B",
        "X",
        "Y",
        # "Z",
        # "START",
        "D_UP",
        "D_DOWN",
        "D_LEFT",
        "D_RIGHT",
        "L",
        "R",
    ]

    sticks = ["MAIN", "C"]

    if can_pause:
        buttons.append("START")
        buttons.append("Z")

    while True:
        button = random.choice(buttons)
        if button in ["Y", "X"]:
            press_button(button, delay=random.uniform(0.1, 2))
        press_button(button, delay=random.uniform(0.1, 0.2))

        send_command(f"SET C 0.5 0.5", pipe_path)
        if random.uniform(0, 1) > 0.5:
            for stick in ["MAIN"]:
                # go up more often
                x, y = random.uniform(0, 1), random.uniform(0, 0.6)
                while ((x - 0.5) ** 2 + (y - 0.5) ** 2) > 0.25:
                    x, y = random.uniform(0, 1), random.uniform(0, 1)

                send_command(f"SET {stick} {x} {y}", pipe_path)
        # time.sleep(random.uniform(0, 0.05))


def join():
    press_button("START")
    time.sleep(2)
    press_button("A")
    time.sleep(0.5)
    press_button("D_LEFT")
    time.sleep(0.5)
    press_button("A")
    time.sleep(0.5)


def main():
    # python3 fuzz.py --join (boolean)
    parser = argparse.ArgumentParser()
    parser.add_argument("--join", action="store_true")
    parser.add_argument("--leave", action="store_true")
    parser.add_argument("--pause", action="store_true")
    args = parser.parse_args()

    # Write the configuration
    write_config(config_path, config_str)

    # Ensure the pipe exists
    ensure_pipe(pipe_path)

    if args.leave:
        join()
    else:
        if args.join:
            join()

        fuzz(args.pause)


if __name__ == "__main__":
    main()
