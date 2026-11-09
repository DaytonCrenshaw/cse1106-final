| Test | Action | Expected Result | Actual Results |
| --- | --- | --- | --- |
| TC01 | Start and select status | `0 / 5`, SPACE AVAILABLE, LED OFF | `0 / 5`, SPACE AVAILABLE, LED OFF |
| TC02 | Record two entries | `2 / 5`, SPACE AVAILABLE, LED OFF | `2 / 5`, SPACE AVAILABLE, LED OFF |
| TC03 | Fill room to five students | `5 / 5`, ROOM FULL, LED ON | `5 / 5`, ROOM FULL, LED ON |
| TC04 | Attempt a sixth entry | Entry denied; remains `5 / 5` | Entry denied; remains `5 / 5` |
| TC05 | Attempt an exit from an empty room | Exit denied; remains `0 / 5` | Exit denied; remains `0 / 5` |
| TC06 | Set capacity to 3 and enter three students | `3 / 3`, ROOM FULL, LED ON | `3 / 3`, ROOM FULL, LED ON |
| TC07 | Attempt to set capacity below occupancy | Change denied; previous capacity retained | Change denied; previous capacity retained |
| TC08 | Exit when the room is full | Count decreases; LED OFF | Count decreases; LED OFF |
| TC09 | Lower capacity to equal current occupancy | ROOM FULL; LED ON | ROOM FULL; LED ON |
