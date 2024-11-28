const users = ['sojeong', 'heeran', 'bojeong'];

    // querySelector를 이용하여 html의 element를 가져와 js에서 사용

    const member_div = document.querySelector('.member_div');
    const add = document.querySelector('.add');

  
    // 원래 저장되어있던 member 목록(sojeong, heeran, bojeong)의 프로필을 보여줌

    const user_icons = () => {
    users.reverse();
    users.map((cur_elem) => {
        member_div.insertAdjacentHTML('afterbegin', 
        `<button class="btn" onclick="location.href='${cur_elem}/${cur_elem}.html'"><span>${cur_elem}</span></button>`);
    })
    };


    // Add 버튼을 누르면 프로필 생성

    add.addEventListener('click', () => {
    let name = prompt('please enter your name');

    if(name != null && !users.includes(name)){
        users.push(name);
        console.log(users);
        member_div.insertAdjacentHTML('afterbegin', 
        `<button class="btn"><span>${name}</span></button>`);
    } else{
        alert('username already exist');
    }
    })

    user_icons();