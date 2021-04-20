const e = React.createElement

class App extends React.Component {
  constructor(props) {
    super(props)
    this.state = { liked: false }
  }
  render() {
    if (this.state.liked) {
      return 'You Liked this.'
    }
    return e(
      'button',
      {
        onClick: () => this.setState({ liked: true }),
      },
      'Like'
    )
  }
}
ReactDOM.render(e(App), document.querySelector('#app'))
