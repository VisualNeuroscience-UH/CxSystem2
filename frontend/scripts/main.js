
function setupTabs() {
    document.querySelectorAll(".tabs__button").forEach(button => {
        button.addEventListener("click", () => {
            const topBar = button.parentElement;
            const tabsContainer = topBar.nextElementSibling; 
            const tabNumber = button.dataset.forTab; 
            const tabToActivate = tabsContainer.querySelector(`.tabs__content[data-tab="${tabNumber}"]`);
            
            // console.log (topBar);
            // console.log (tabsContainer);
            // console.log (tabNumber);
            // console.log (tabToActivate);
            topBar.querySelectorAll('.tabs__button').forEach(button => {
                button.classList.remove("tabs__button--active");
            })
            tabsContainer.querySelectorAll('.tabs__content').forEach(tab => {
                tab.classList.remove("tabs__content--active");
            })

            button.classList.add("tabs__button--active");
            tabToActivate.classList.add("tabs__content--active");
        })
    })
}

function add_to_overview_tab(inp_data){
    var overview = document.querySelector('.tabs__content[data-tab="1"]');
    overview.innerHTML = "<p>" + inp_data +"</p>"  +overview.innerHTML;
}


document.addEventListener("DOMContentLoaded",() => {
    setupTabs();

    document.querySelectorAll(".tabs__topbar").forEach(tabsContainer => {
        tabsContainer.querySelector(".tabs__button").click();
    })
})

Split(['.tabsdiv','.paramsdiv'],{
    gutterSize: 3,
    sizes: [70,40],
    minSize:[300,300]
});






var json_input;
document.getElementById('fileChooser').onchange = function () {
    var file = this.files[0];
    var reader = new FileReader();
    reader.readAsText(file);
    reader.onload = function () {
        // console.log(this.result);
        json_input = JSON.parse(this.result); 
        document.querySelector('[overview-tag="filename"]').innerHTML = "<p class='overviewlines'> Loaded Filename: </p> " +  file.name ; 
        
        
        function show(json) {
            var content = '<table class="overview_table" id="myTable" border=1>';
            var key_idx= 0 ;
            for (var key in json) {
                content += 
                 '<tr id =' + key_idx + '>' +
                    '<td class="td_editbox">' +
                        '<span id="key_' + key_idx + '" class="text">' + key + '</span>' + 
                    '</td>' + 
                    '<td class="td_editbox">' +
                        '<span><input type="text" value="' + json[key] + '" text_input_id="value_' + key_idx + '" /></span>'+
                    '</td>' + 
                    '<td class="td_editbox">' +
                        '<button class="table__savebutton" save_button_id="value_' + key_idx+'" id="TableFieldSaveButton">save</button>'+
                    '</td>' + 
                '</tr>';
                key_idx+=1; 
            }
            content += '</table>';
            $('div[overview-tag="simulation-params"]').append(content);
        }    

        $(document).on("keyup", "input:text", function (e) {
            let current_key_idx = get_key_idx($(this).attr('text_input_id'));
            let current_value = String(json_input.params[Object.keys(json_input.params)[current_key_idx]]);
            if ($(this).val() != current_value){ // check to save only if the value is changed
                $('button[save_button_id="' + $(this).attr('text_input_id') + '"]').removeClass('table__savebutton')
                if (e.which === 13 || e.which === 9) {
                    json_input.params[Object.keys(json_input.params)[current_key_idx]] = $(this).val(); // change the value in the json 
                    $('button[save_button_id="' + $(this).attr('text_input_id') + '"]').addClass('table__savebutton'); // hide the button 
                }    
            }
            else{ // hide the save button since the values are again the same 
                $('button[save_button_id="' + $(this).attr('text_input_id') + '"]').addClass('table__savebutton');
            }
        });
        
        
        $(document).on("click","#TableFieldSaveButton",function(){
            
            let current_key_idx = get_key_idx($(this).attr('save_button_id'));
            let changed_val = $('input[text_input_id="' + $(this).attr('save_button_id') + '"]').val()
            json_input.params[Object.keys(json_input.params)[current_key_idx]] = changed_val; // change the value in the json 
            $('button[save_button_id="' + $(this).attr('save_button_id') + '"]').addClass('table__savebutton');
            // alert("to be implemented!");
        });

    
        show(json_input.params);

        function get_key_idx(inp_tag_value){
            let length = inp_tag_value.split('_').length;
            return parseInt(inp_tag_value.split('_')[length-1]);
        }
    };
    
};

function downloadjson(){
    var data = "text/json;charset=utf-8," + encodeURIComponent(JSON.stringify(json_input));
    var a = document.createElement('a');
    a.href = 'data:' + data;
    a.download = 'data.json';
    a.innerHTML = 'download JSON';

    var container = document.getElementById('container');
    container.appendChild(a);
}

var ajv = new Ajv();
var schema = {
    "properties": {
      "foo": { "type": "string" },
      "bar": { "type": "number", "maximum": 3 }
    }
  };
  var data = {"foo": "abc", "bar": 2333}
  var validate = ajv.compile(schema);
  var valid = validate(data);
  console.log(validate.errors);
// test({"foo": "abc", "bar": 2});
// test({"foo": 2, "bar": 4});

// function test(data) {
//   var valid = validate(data);
//   if (valid) console.log('Valid!');
//   else console.log('Invalid: ' + ajv.errorsText(validate.errors));
// }