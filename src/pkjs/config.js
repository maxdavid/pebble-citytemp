module.exports = [
  {
    type: 'heading',
    defaultValue: 'Configuration'
  },
  {
    type: 'text',
    defaultValue: '<h6>A white button = OFF <br> An orange button = ON</h6>'
  },
  {
    type: 'section',
    items: [
      {
        type: 'heading',
        defaultValue: '<h5>Weather</h5>'
      },
      /*
            {
                "type": "toggle",
                "messageKey": "use_gps",
                "label": "Use GPS",
                "description": "If you want to conserve some battery, have GPS=NO AND enter your city name or zip code.",
                "defaultValue": true
            },
            {
                "type": "input",
                "messageKey": "zip_code",
                "label": "Zip Code",
                "description": "You <strong>must</strong> enter a zip code or city name if \"Use GPS\" is NO.",
                "defaultValue": ""
            },
            {
                "type": "input",
                "messageKey": "city_name",
                "label": "City",
                "description": "You <strong>must</strong> enter a zip code or city name if \"Use GPS\" is NO.",
                "defaultValue": ""
            },
            */
      {
        type: 'radiogroup',
        messageKey: 'units',
        label: 'Temp. Units',
        defaultValue: 'fahrenheit',
        options: [
          {
            label: 'Celsius',
            value: 'celsius'
          },
          {
            label: 'Fahrenheit',
            value: 'fahrenheit'
          }
        ]
      }
      //           {
      //             "type": "toggle",
      //           "messageKey": "weatherstatus",
      //         "label": "Hide weather",
      //       "defaultValue": false
      // },
    ]
  },
  {
    type: 'section',
    items: [
      {
        type: 'heading',
        defaultValue: '<h5>Display</h5>'
      },

      {
        type: 'select',
        messageKey: 'background',
        defaultValue: '0.',
        label: 'City',
        options: [
          {
            label: '< Default/Blank >',
            value: '0.'
          },
          {
            label: '< RANDOM >',
            value: '1.'
          },
          {
            label: 'Athens',
            value: '2.'
          },
          {
            label: 'Auckland',
            value: '3.'
          },
          {
            label: 'Bangkok',
            value: '4.'
          },
          {
            label: 'Beijing',
            value: '5.'
          },
          {
            label: 'Berlin',
            value: '6.'
          },
          {
            label: 'Bishkek',
            value: '39.'
          },
          {
            label: 'Bogota',
            value: '7.'
          },
          {
            label: 'Brisbane',
            value: '8.'
          },
          {
            label: 'Calgary',
            value: '9.'
          },
          {
            label: 'Canberra',
            value: '10.'
          },
          {
            label: 'Chicago',
            value: '11.'
          },
          {
            label: 'Delhi',
            value: '12.'
          },
          {
            label: 'Dubai',
            value: '13.'
          },
          {
            label: 'Dublin',
            value: '14.'
          },
          {
            label: 'Hong Kong',
            value: '15.'
          },
          {
            label: 'London',
            value: '16.'
          },
          {
            label: 'Los Angeles',
            value: '17.'
          },
          {
            label: 'Madrid',
            value: '18.'
          },
          {
            label: 'Melbourne',
            value: '19.'
          },
          {
            label: 'Milan',
            value: '20.'
          },
          {
            label: 'Moscow',
            value: '21.'
          },
          {
            label: 'New York',
            value: '22.'
          },
          {
            label: 'Paris',
            value: '23.'
          },
          {
            label: 'Portland',
            value: '24.'
          },
          {
            label: 'Rio de Janeiro',
            value: '25.'
          },
          {
            label: 'Rome',
            value: '26.'
          },
          {
            label: 'Rotterdam',
            value: '40.'
          },
          {
            label: 'San Francisco',
            value: '27.'
          },
          {
            label: 'Seattle',
            value: '28.'
          },
          {
            label: 'Seoul',
            value: '29.'
          },
          {
            label: 'Shanghai',
            value: '30.'
          },
          {
            label: 'Singapore',
            value: '31.'
          },
          {
            label: 'St. Petersburg',
            value: '32.'
          },
          {
            label: 'Sydney',
            value: '33.'
          },
          {
            label: 'Tokyo',
            value: '34.'
          },
          {
            label: 'Toronto',
            value: '35.'
          },
          {
            label: 'Vancouver',
            value: '36.'
          },
          {
            label: 'Washington DC',
            value: '37.'
          },
          {
            label: 'Wellington',
            value: '38.'
          }
        ]
      },

      {
        type: 'select',
        messageKey: 'format',
        defaultValue: '0.',
        label: 'Temp. Format',
        options: [
          {
            label: 'Large',
            value: '0.'
          },
          {
            label: 'Small',
            value: '1.'
          },
          {
            label: 'None',
            value: '2.'
          }
        ]
      },
      {
        type: 'toggle',
        messageKey: 'ampmsecs',
        label: 'Big Time',
        defaultValue: false
      }
    ]
  },
  {
    type: 'section',
    items: [
      {
        type: 'heading',
        defaultValue: '<h5>Vibration</h5>'
      },
      {
        type: 'toggle',
        messageKey: 'bluetoothvibe_status',
        label: 'Bluetooth vibration',
        defaultValue: false
      },
      {
        type: 'toggle',
        messageKey: 'hourlyvibe',
        label: 'Hourly vibration',
        defaultValue: false
      }
    ]
  },
  {
    type: 'submit',
    defaultValue: 'Save Settings'
  },
  {
    type: 'text',
    defaultValue:
      "<h6><center>Original code by Mark Reed. <br> Update by Max David. <br> <a href='http://github.com/maxdavid/pebble-citytemp'>Github Link</a></center></h6>"
  }
];
