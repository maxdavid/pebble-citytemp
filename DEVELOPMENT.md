# Development

These are mostly personal notes for whenever I need to return to Pebble/Rebble development.

## Building

```
$ pebble wipe && pebble build

# and optionally
$ pebble clean
```

## Emulator

```
$ pebble install --logs --emulator basalt build/pebble-citytemp.pbw
```

### Modifying for Emulation / Testing

#### `src/pkjs/app.js`

The `options` object (line 58) needs to be modified to:

```
options = {
    "use_gps" : false,
    "units" : "fahrenheit",
    "hideweather" : false,
    "city_name" : "Seattle",
    "zip_code" : "98112"
}
```

Manually overriding line 104 can be helpful for testing different weather icons.

#### `src/c/citytemp.c`

Temperature reading size: line 747

City background image: line 748 (cross reference with `src/pkjs/config.js`)
