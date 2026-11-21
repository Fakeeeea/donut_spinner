# Donut spinner

<div align="center">
    <img src="assets/showcase.png" alt="donut_image" width="50%">
</div>

Encode a file into a video of a spinning donut!
Each byte is converted into a frame of a donut, each representing a certain angle.
The donut, by spinning from one angle to another, encodes a certain file. The decoder just waits
for stall frames to extract the original file bytes.

> [!IMPORTANT]
> A media player able to process .y4m videos is required (eg. vlc)

## Usage

| Flag | Description | Note |
|---|---| --- |
|-i | Sets input file| Required|
|-o | Sets output file| By default "input.y4m" |
|-d| Sets decoding mode |

For example,

```
./donut_spinner -i"raw.txt" -o"encoded.y4m"

./donut_spinner -d -i"encoded.y4m" -o"decoded.txt
```

> [!CAUTION]
> Feeding big files into the encoder might not be a smart idea.
> Only normal letters 13kb → 340kb; File with many symbols (having far apart ASCII codes) might lead to
> even bigger sizes