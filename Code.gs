// change [YOUR_SPREADSHEET_URL] to your spreadsheet
function doGet(e) {
  var action = e.parameter.action;

  if (action === "saveData") {
    var value1 = e.parameter.value1;
    var value2 = e.parameter.value2;
    var value3 = e.parameter.value3;
    var value4 = e.parameter.value4;
    var value5 = e.parameter.value5;
    save_data(value1, value2, value3, value4, value5);
  }
  else if (action === "fetchData") {
    var data = fetch_data(); // Fetch data from cell A35
    return ContentService.createTextOutput(data);
  } 
  else {
    return ContentService.createTextOutput("Invalid action");
  }
  
}

function save_data(value1, value2, value3, value4, value5) {
  var ss = SpreadsheetApp.openByUrl("https://docs.google.com/spreadsheets/d/[YOUR_SPREADSHEET_URL]/edit");
  var dataLoggerSheet = ss.getSheetByName("DataCollector");
  
  dataLoggerSheet.getRange("H11").setValue(value1);
  dataLoggerSheet.getRange("I11").setValue(value2);
  dataLoggerSheet.getRange("J11").setValue(value3);
  dataLoggerSheet.getRange("K11").setValue(value4);
  dataLoggerSheet.getRange("L11").setValue(value5);
}

function fetch_data() {
  var ss = SpreadsheetApp.openByUrl("https://docs.google.com/spreadsheets/d/[YOUR_SPREADSHEET_URL]/edit");
  var dataLoggerSheet = ss.getSheetByName("DataCollector");

  // Get the value from cell A35
  var value = dataLoggerSheet.getRange("A35").getValue();
  return value.toString(); // Ensure the return value is a string
}
